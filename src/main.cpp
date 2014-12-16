/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *    Description:  main src file, contains entry point
 *
 *        Version:  1.0
 *        Created:  12/15/2014 02:24:40 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mohamed Ashraf (m0hamed), Hossam Ahmed (hossam-mossalam)
 *   Organization:  GUC
 *
 * =====================================================================================
 */

#include "globals.h"
#include "file_utils.h"
#include "sift_utils.h"
#include "classifier_utils.h"
using cv::Rect;

int main() {
  vector<Mat> car_descriptors = get_category_sift_descriptors(CAR_IMAGES_PATH);
  vector<Mat> bike_descriptors = get_category_sift_descriptors(BIKE_IMAGES_PATH);
  vector<Mat> cow_descriptors = get_category_sift_descriptors(COW_IMAGES_PATH);

  vector<Mat> car_vocab = pick_random_images(car_descriptors, VOCAB_ITEMS_PER_CATEGORY);
  vector<Mat> bike_vocab = pick_random_images(bike_descriptors, VOCAB_ITEMS_PER_CATEGORY);
  vector<Mat> cow_vocab = pick_random_images(cow_descriptors, VOCAB_ITEMS_PER_CATEGORY);

  car_vocab.reserve(car_vocab.size() + bike_vocab.size() + cow_vocab.size());
  car_vocab.insert(car_vocab.end(), bike_vocab.begin(), bike_vocab.end());
  car_vocab.insert(car_vocab.end(), cow_vocab.begin(), cow_vocab.end());
  bike_vocab.clear();
  cow_vocab.clear();
  vector<Mat> full_vocab = car_vocab;
  car_vocab.clear();

  Mat samples(full_vocab.size() * full_vocab.at(0).rows, full_vocab.at(0).cols, CV_8UC1);
  for (int i = 0; i < full_vocab.size(); i++) {
    full_vocab.at(i).copyTo(samples(Rect(0,i *full_vocab.at(i).rows ,
        full_vocab.at(i).cols,full_vocab.at(i).rows)));
  }

  Mat temp;
  samples.convertTo(temp, CV_32FC1);
  samples = temp;

  Mat centers;
  Mat labels;
  cv::kmeans(samples, CENTROIDS_COUNT, labels, cv::TermCriteria(1, 100, 2), 1,
                cv::KMEANS_RANDOM_CENTERS, centers);

  car_descriptors.reserve(car_descriptors.size() + bike_descriptors.size() +
                              cow_descriptors.size());
  car_descriptors.insert(car_descriptors.end(), bike_descriptors.begin(),
                              bike_descriptors.end());
  car_descriptors.insert(car_descriptors.end(), cow_descriptors.begin(),
                              cow_descriptors.end());
  bike_descriptors.clear();
  cow_descriptors.clear();
  vector<Mat> full_descriptors = car_descriptors;
  car_descriptors.clear();

  double dist;
  Mat histograms = Mat::zeros(full_descriptors.size(), centers.rows, CV_32SC1);

  for (int k = 0; k < full_descriptors.size(); k++) {
    for (int i = 0; i < full_descriptors.at(k).rows; i++) {
      double min_distance = std::numeric_limits<double>::infinity();
      int center_index = -1;
      Mat current_sample = full_descriptors.at(k).row(i);
      for (int j = 0; j < centers.rows; j++) {
        Mat current_center = centers.row(j);
        dist = norm(current_sample, current_center, cv::NORM_L2);
        if(dist < min_distance){
          min_distance = dist;
          center_index = j;
        }
      }
      histograms.at<int>(k,center_index)++;
    }
  }
  return 0;
}
