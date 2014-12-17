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
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <time.h>
using cv::Size;

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
  Mat histograms = Mat::zeros(full_descriptors.size(), centers.rows, CV_32SC1);
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
      histograms.at<int>(k,center_index)++;
    }
  }
  return histograms;
}