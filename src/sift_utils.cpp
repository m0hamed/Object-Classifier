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

vector<KeyPoint> create_dense_keypoints(int rows, int cols, int grid_size) {
  vector<KeyPoint> points;
  for (int i=0; i<rows; i += grid_size) {
    for (int j=0; j<cols; j += grid_size) {
      points.push_back(KeyPoint(i, j, grid_size));
    }
  }
  return points;
}

vector<Mat> get_category_sift_descriptors(string category_path) {
  vector<string> car_images = get_files_in_directory(category_path);
  vector<Mat> category_sift_descriptors;
  for(string image_path : car_images) {
    cout << "Currently processing " << image_path << endl;
    Mat image = imread(image_path, 0);
    equalizeHist(image, image);
    Mat image_resized;
    resize(image, image_resized, Size(300, 250));
    cv::SiftDescriptorExtractor extractor;
    Mat sift_descriptors;
    vector<KeyPoint> keypoints = create_dense_keypoints(300, 250, 5);
    extractor.compute(image_resized, keypoints, sift_descriptors);
    category_sift_descriptors.push_back(sift_descriptors);
  }
}

