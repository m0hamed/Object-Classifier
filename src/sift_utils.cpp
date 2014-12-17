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
using cv::imread;
using cv::Size;

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

void create_sift_descs(const string path, int* num_classes) {
  vector<string> class_paths = get_files_in_directory(path);
  *num_classes = class_paths.size();
  string desc_path = DESC_PATH;
  for (string class_path : class_paths) {
    vector<string> category_images = get_files_in_directory(path + class_path);
    vector<Mat> descs = get_category_sift_descriptors(path + class_path + "/",
        category_images);
    for (int i = 0; i < descs.size(); i++)
      write_file(desc_path + class_path + "/" + category_images[i], descs[i],
          "Dense sift descriptors"); 
  }
}
