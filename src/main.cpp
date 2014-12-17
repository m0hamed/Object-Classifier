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

  vector<Mat> car_vocab = pick_random_images(car_descriptors,
                                              VOCAB_ITEMS_PER_CATEGORY);
  vector<Mat> bike_vocab = pick_random_images(bike_descriptors,
                                              VOCAB_ITEMS_PER_CATEGORY);
  vector<Mat> cow_vocab = pick_random_images(cow_descriptors,
                                              VOCAB_ITEMS_PER_CATEGORY);

  vector<Mat> full_vocab = combine_vectors_of_mat(car_vocab, cow_vocab,
                                                    bike_vocab);

  Mat samples(full_vocab.size() * full_vocab.at(0).rows, full_vocab.at(0).cols,
                CV_8UC1);
  for (int i = 0; i < full_vocab.size(); i++) {
    full_vocab.at(i).copyTo(samples(Rect(0, i * full_vocab.at(i).rows,
        full_vocab.at(i).cols, full_vocab.at(i).rows)));
  }

  samples.convertTo(samples, CV_32FC1);
  Mat centers;
  Mat labels;
  cv::kmeans(samples, CENTROIDS_COUNT, labels,
              cv::TermCriteria(cv::TermCriteria::COUNT, ITERATIONS, EPSILON),
              ATTEMPTS, cv::KMEANS_RANDOM_CENTERS, centers);

  vector<Mat> full_descriptors = combine_vectors_of_mat(car_descriptors,
              cow_descriptors, bike_descriptors);

  Mat histograms = get_histograms(full_descriptors, centers);
  return 0;
}