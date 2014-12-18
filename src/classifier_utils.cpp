/*
 * =====================================================================================
 *
 *       Filename:  sift_utils.cpp
 *
 *    Description:  A collection of helper functions related to sift
 *
 *        Version:  1.0
 *        Created:  12/15/2014 11:37:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Hossam Ahmed (hossam-mossalam)
 *   Organization:  GUC
 *
 * =====================================================================================
 */

#include "classifier_utils.h"

using cv::Size;
using cv::Rect;

Mat make_labels(int class_id, vector<int> class_labels, vector<int> indeces){
  Mat labels(indeces.size(), 1, CV_32SC1);
  for (int i = 0; i < indeces.size(); i++) 
    labels.at<int>(i) = class_id == class_labels[indeces[i]];
  return labels;
}

void build_classifiers(const string bows_path) {
  vector<int> labels;
  int num_classes;
  vector<string> class_paths = get_files_in_directory(bows_path);
  Mat features = read_bows(class_paths, bows_path, labels, &num_classes);
  int training_size = (int) (TRAINING_DATA_SIZE * features.rows);

  vector<int> indeces;
  for (int i = 0; i < features.rows; i++)
    indeces.push_back(i); 
  std::random_shuffle(indeces.begin(), indeces.end());

  Mat training_set(training_size, features.cols, CV_32FC1);
  for (int i = 0; i < training_size; i++) 
    training_set.row(i) = features.row(indeces[i]);
  cout << training_size << endl;

  Mat testing_set(features.rows - training_size, features.cols,
      CV_32FC1); 
  for (int i = training_size; i < features.rows; i++)
    testing_set.row(i - training_size) = features.row(indeces[i]);

  for (int i = 0; i < num_classes; i++) {
    cout << i << ". Classifier " << class_paths[i] << " :" << endl;
    cout << "training...";
      Mat pos_labels = make_labels(i, labels, indeces);
      CvNormalBayesClassifier nb_class( CvNormalBayesClassifier(training_set,
            pos_labels(cv::Rect(0, 0, 1, training_set.rows))));
      cout << "Ok" << endl;
  
      cout << "evaluating...";
      double acc = eval_classifier(nb_class, testing_set,
          pos_labels(Rect(0, training_set.rows, 1, testing_set.rows)));
      cout << "Ok" << endl;
      cout << "Acc = " << acc * 100 << "%" << endl;
    } 
} 

Mat read_bows(const vector<string> class_paths, const string bow_path,
    vector<int>& labels, int* num_classes) {
  cout << "reading bows...";
  *num_classes = class_paths.size();
  vector<string> im_names;
  vector<string> bow_prefix;
  for (int i = 0; i < *num_classes; i++) {
    vector<string> tmp = get_files_in_directory(bow_path + class_paths[i]);
    vector<string> tmp_prefix(tmp.size(), bow_path + class_paths[i] + "/");
    vector<int> tmp_labels(tmp.size(), i);
    im_names.insert(im_names.end(), tmp.begin(), tmp.end());
    bow_prefix.insert(bow_prefix.end(), tmp_prefix.begin(), tmp_prefix.end());
    labels.insert(labels.end(), tmp_labels.begin(), tmp_labels.end());
  }

  int cols, rows;
  read_meta(bow_prefix[0] + im_names[0], "BOW", &rows,
      &cols);
  Mat features(im_names.size() * rows, cols, CV_32SC1);
  cout << features.size() << endl;
  for (int i = 0; i < im_names.size(); i++) {
    Mat roi = features(cv::Rect(0, i, cols, rows));
    read_file(bow_prefix[i] + im_names[i], "BOW", roi); 
  }
  cout << "Ok" << endl;
  return features;

}

double eval_classifier(const CvNormalBayesClassifier& nb_classifier, const Mat&
    testing_set, const Mat& labels) {
  Mat result;
  nb_classifier.predict(testing_set, &result);
  int correct = 0;
  for (int i = 0; i < result.rows; i++) {
    correct += labels.at<int>(i) == result.at<float>(i);
  }
  return correct / (double) testing_set.rows;
}
