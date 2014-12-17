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
#include <opencv2/ml/ml.hpp>

using cv::Rect;

int main() {

  int num_classes;
//  create_sift_descs(IMAGES_PATH, DESC_PATH, &num_classes);
    create_bows(DESC_PATH, BOW_PATH, &num_classes);
  return 0;
//  int num_cars, num_bikes, num_cows;
//  vector<Mat> car_descriptors = get_category_sift_descriptors(CAR_IMAGES_PATH);
//  num_cars = car_descriptors.size();
//  vector<Mat> bike_descriptors = get_category_sift_descriptors(BIKE_IMAGES_PATH);
//  num_bikes = bike_descriptors.size();
//  vector<Mat> cow_descriptors = get_category_sift_descriptors(COW_IMAGES_PATH);
//  num_cows = cow_descriptors.size();
//
//  vector<Mat> car_vocab = pick_random_images(car_descriptors,
//                                              VOCAB_ITEMS_PER_CATEGORY);
//  vector<Mat> bike_vocab = pick_random_images(bike_descriptors,
//                                              VOCAB_ITEMS_PER_CATEGORY);
//  vector<Mat> cow_vocab = pick_random_images(cow_descriptors,
//                                              VOCAB_ITEMS_PER_CATEGORY);
//
//  vector<Mat> full_vocab = combine_vectors_of_mat(car_vocab, cow_vocab,
//                                                    bike_vocab);
//
//  Mat samples(full_vocab.size() * full_vocab.at(0).rows, full_vocab.at(0).cols,
//                CV_8UC1);
//  for (int i = 0; i < full_vocab.size(); i++) {
//    full_vocab.at(i).copyTo(samples(Rect(0, i * full_vocab.at(i).rows,
//        full_vocab.at(i).cols, full_vocab.at(i).rows)));
//  }
//
//  samples.convertTo(samples, CV_32FC1);
//  Mat centers;
//  Mat labels;
//  cout << "Running Kmeans...";
//  cv::kmeans(samples, CENTROIDS_COUNT, labels,
//              cv::TermCriteria(cv::TermCriteria::COUNT, ITERATIONS, EPSILON),
//              ATTEMPTS, cv::KMEANS_RANDOM_CENTERS, centers);
//
//  vector<Mat> full_descriptors = combine_vectors_of_mat(car_descriptors,
//              cow_descriptors, bike_descriptors);
//  cout << "Ok" << endl;
//
//  cout << "Extracting feature vectors...";
//  Mat histograms = get_histograms(full_descriptors, centers);
//  cout << "Ok" << endl;
//  cout << histograms.size() << endl;
//
//  //marked for rewriting into better code
//  vector<int> car_labels(num_cars, 0);
//  vector<int> bikes_labels(num_bikes, 1);
//  vector<int> cows_labels(num_cows, 2);
//  vector<int> full_labels;
//  full_labels.reserve(car_labels.size() + bikes_labels.size() +
//      cows_labels.size());
//  full_labels.insert(full_labels.begin(), car_labels.begin(), car_labels.end());
//  full_labels.insert(full_labels.begin() + num_cars, bikes_labels.begin(),
//      bikes_labels.end());
//  full_labels.insert(full_labels.begin() + num_cows, cows_labels.begin(),
//      cows_labels.end());
//
//  cout << "Building classifiers..." << endl;
//  vector<CvNormalBayesClassifier*> classifiers =  build_classifiers(3, histograms, full_labels);
//
//  return 0;
}
