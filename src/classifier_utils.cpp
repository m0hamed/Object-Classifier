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