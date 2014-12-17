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
 *         Author:  Mohamed Ashraf (m0hamed)
 *   Organization:  GUC
 *
 * =====================================================================================
 */

#include "sift_utils.h"
#include "file_utils.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>

using cv::imread;
using cv::Size;
using cv::Rect;

vector<KeyPoint> create_dense_keypoints(int rows, int cols, int grid_size) {
  vector<KeyPoint> points;
  for (int i=0; i<rows; i += grid_size) {
    for (int j=0; j<cols; j += grid_size) {
      points.push_back(KeyPoint(i, j, grid_size));
    }
  }
  return points;
}

vector<Mat> get_category_sift_descriptors(const string prefix, const vector<string>& category_images) {
  vector<Mat> category_sift_descriptors;
  for(string image_path : category_images) {
    cout << "Currently processing " << image_path << endl;
    Mat image = imread(prefix + image_path, 0);
    equalizeHist(image, image);
    Mat image_resized;
    resize(image, image_resized, Size(300, 250));
    cv::SiftDescriptorExtractor extractor;
    Mat sift_descriptors;
    vector<KeyPoint> keypoints = create_dense_keypoints(300, 250, 5);
    extractor.compute(image_resized, keypoints, sift_descriptors);
    category_sift_descriptors.push_back(sift_descriptors);
  }
  return category_sift_descriptors;
}

void create_sift_descs(const string im_path, const string desc_path, int* num_classes) {
  vector<string> class_paths = get_files_in_directory(im_path);
  *num_classes = class_paths.size();
  for (string class_path : class_paths) {
    vector<string> category_images = get_files_in_directory(im_path + class_path);
    vector<Mat> descs = get_category_sift_descriptors(im_path + class_path + "/",
        category_images);
    for (int i = 0; i < descs.size(); i++)
      write_file(desc_path + class_path + "/" + category_images[i], descs[i],
          "Dense sift descriptors"); 
  }
}

void create_bows(const string desc_path, const string bow_path, int* num_classes) {
  vector<int> class_size;
  vector<string> im_names;
  int im_rows;

  Mat samples = read_descs(desc_path, im_names, class_size, num_classes, &im_rows);

  Mat vocab = create_vocab(samples, class_size, *num_classes, im_rows);
  Mat centers, labels;
  cv::kmeans(vocab, CENTROIDS_COUNT, labels,
      cv::TermCriteria(cv::TermCriteria::COUNT, ITERATIONS, EPSILON), ATTEMPTS,
      cv::KMEANS_RANDOM_CENTERS, centers);
  Mat histograms = get_histograms(samples, centers, im_rows);

  write_bows(desc_path, bow_path, histograms, im_names, class_size);
}

Mat read_descs(const string desc_path, vector<string>& im_names, vector<int>& class_size, 
    int* num_classes, int* im_rows) {
  cout << "reading descriptors...";
  vector<string> class_paths = get_files_in_directory(desc_path);
  *num_classes = class_paths.size();
  vector<string> desc_prefix;
  for (string class_path : class_paths) {
    vector<string> tmp = get_files_in_directory(desc_path + class_path);
    vector<string> tmp_prefix(tmp.size(), desc_path + class_path + "/");
    class_size.push_back(tmp.size());
    im_names.insert(im_names.end(), tmp.begin(), tmp.end());
    desc_prefix.insert(desc_prefix.end(), tmp_prefix.begin(), tmp_prefix.end());
  }

  int cols;
  read_meta(desc_prefix[0] + im_names[0], "Dense sift descriptors", im_rows,
      &cols);
  Mat samples(im_names.size() * *im_rows, cols, CV_32FC1);
  for (int i = 0; i < im_names.size(); i++) {
    Mat roi = samples(cv::Rect(0, i * *im_rows, cols, *im_rows));
    read_file(desc_prefix[i] + im_names[i], "Dense sift descriptors", roi); 
  }
  cout << "Ok" << endl;
  return samples;
}

Mat create_vocab(const Mat samples, const vector<int> class_size, const int
    num_classes, const int im_rows) {
  int sample = 0, base = 0;
  Mat vocab(num_classes * VOCAB_ITEMS_PER_CATEGORY * im_rows, samples.cols, CV_32FC1);
  cout << "creating vocab...";

  for (int c = 0; c < num_classes; c++) {
    int size = class_size[c];
    vector<int> indeces;
    for (int i = 0; i < size; i++)
      indeces.push_back(i);
    std::random_shuffle(indeces.begin(), indeces.end());
    for (int i = 0; i < VOCAB_ITEMS_PER_CATEGORY; i++) {
      Rect roi_samples(0, (indeces[i] + base) * im_rows, samples.cols, im_rows);
      Rect roi_vocab(0, sample * im_rows, vocab.cols, im_rows);
      samples(roi_samples).copyTo(vocab(roi_vocab));
      sample++;
    }
    base += size;
  }
  cout << "Ok" << endl;
  return vocab;
}

Mat get_histograms(const Mat& samples, const Mat& centers, const int im_rows) {
  cout << "encoding images...";
  Mat histograms = Mat::zeros(samples.rows / im_rows, centers.rows, CV_32SC1);
  for (int sample = 0; sample < samples.rows; sample++) {
      double min_distance = std::numeric_limits<double>::infinity();
      int center_index = -1;
      for (int center = 0; center < centers.rows; center++) {
        double dist = norm(samples.row(sample), centers.row(center), cv::NORM_L2);
        if(dist < min_distance) {
          min_distance = dist;
          center_index = center;
        }
      }
      histograms.at<int>(sample / im_rows, center_index)++;
  }
  cout << "Ok" << endl;
  return histograms;
}

void write_bows(const string desc_path, const string bow_path, const Mat& hist,
    const vector<string>& im_names, const vector<int>& class_size) {
  vector<string> class_paths = get_files_in_directory(desc_path);
  int image = 0;
  for (int c = 0; c < class_size.size(); c++) {
    for (int i = 0; i < class_size[c]; i++) {
      string file_path = bow_path + class_paths[c] + "/" + im_names[image];
      write_file(file_path, hist(Rect(0, image, hist.cols, 1)), "BOW");
      image++;
    }
  }
}


