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

vector<Mat> pick_random_images(vector<Mat> category_images, int images_count) {
  vector<int> indices = generate_random_numbers(category_images.size(),
      images_count);
  vector<Mat> picked_images;
  for (int i = 0; i < images_count; i++) {
    picked_images.push_back(category_images.at(indices.at(i)));
  }
  return picked_images;
}

vector<int> generate_random_numbers(int max_value, int count) {
  srand (time(NULL));
  vector<int> generated_numbers (count);
  for(int i = 0; i < count; i++) {
    int num;
    bool exist;
    do {
      exist = false;
      num = rand() % max_value;
      for (int j = 0; j < i; j++) {
        if (generated_numbers.at(j) == num) {
          exist = true;
          break;
        }
      }
    }while(exist);
    generated_numbers.at(i) = num;
  }
  return generated_numbers;
}

vector<Mat> combine_vectors_of_mat(vector<Mat> vec1, vector<Mat> vec2,
    vector<Mat> vec3) {
  vector<Mat> result;
  result.reserve(vec1.size() + vec2.size() + vec3.size());
  result.insert(result.end(), vec1.begin(), vec1.end());
  result.insert(result.end(), vec2.begin(), vec2.end());
  result.insert(result.end(), vec3.begin(), vec3.end());
  return result;
}

Mat get_histograms(vector<Mat> full_descriptors, Mat centers) {
  Mat histograms = Mat::zeros(full_descriptors.size(), centers.rows, CV_32FC1);
  double dist;
  for (int k = 0; k < full_descriptors.size(); k++) {
    for (int i = 0; i < full_descriptors.at(k).rows; i++) {
      double min_distance = std::numeric_limits<double>::infinity();
      int center_index = -1;
      Mat current_sample = full_descriptors.at(k).row(i);
      for (int j = 0; j < centers.rows; j++) {
        Mat current_center = centers.row(j);
        dist = norm(current_sample, current_center, cv::NORM_L2);
        if(dist < min_distance) {
          min_distance = dist;
          center_index = j;
        }
      }
      histograms.at<int>(k, center_index)++;
    }
  }
  return histograms;
}

Mat make_labels(int class_id, vector<int> class_labels, vector<int> indeces){
  Mat labels(indeces.size(), 1, CV_32SC1);
  for (int i = 0; i < indeces.size(); i++) 
    labels.at<int>(i) = class_id == class_labels[indeces[i]];
  return labels;
}

vector<CvNormalBayesClassifier*> build_classifiers(int num_classes, Mat features,
    vector<int> class_labels) {
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

  vector<CvNormalBayesClassifier*> classifiers;
  for (int i = 0; i < num_classes; i++) {
    cout << "Classifier for class " << i + 1 << ":" << endl;
    cout << "training...";
    Mat pos_labels = make_labels(i, class_labels, indeces);
    CvNormalBayesClassifier* nb_class = new CvNormalBayesClassifier(
        CvNormalBayesClassifier(training_set, pos_labels(cv::Rect(0, 0, 1,
              training_set.rows))));
    classifiers.push_back(nb_class);
    cout << "Ok" << endl;

    cout << "evaluating...";
    double acc = eval_classifier(classifiers[i], testing_set,
        pos_labels(Rect(0, training_set.rows, 1, testing_set.rows)));
    cout << "Ok" << endl;
    cout << "Acc of Classifier " << i + 1 << " = " << acc << endl;
  }
  return classifiers;
} 

double eval_classifier(CvNormalBayesClassifier* nb_classifier, Mat testing_set, Mat labels) {
  Mat result;
  nb_classifier->predict(testing_set, &result);
  int correct = 0;
  for (int i = 0; i < result.rows; i++) {
    correct += labels.at<int>(i) == result.at<float>(i);
  }
  return correct / (double) testing_set.rows;
}
