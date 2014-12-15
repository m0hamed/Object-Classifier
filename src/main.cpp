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
 *         Author:  Mohamed Ashraf (m0hamed)
 *   Organization:  GUC
 *
 * =====================================================================================
 */

#include "globals.h"
#include "file_utils.h"
#include "sift_utils.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
using cv::imread;
using cv::Size;

int main() {
  vector<string> car_images = get_files_in_directory(CAR_IMAGES_PATH);
  int image_index = 0;
  for(string image_path : car_images) {
    Mat image = imread(image_path, 0);
    equalizeHist(image, image);
    Mat image_resized;
    resize(image, image_resized, Size(300, 250));
    cv::SiftDescriptorExtractor extractor;
    Mat sift_descriptors;
    vector<KeyPoint> keypoints = create_dense_keypoints(300, 250, 5);
    extractor.compute(image_resized, keypoints, sift_descriptors);
  }
  return 0;
}
