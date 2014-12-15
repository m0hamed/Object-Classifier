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

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "globals.h"
#include "file_utils.h"
using cv::imread;

int main() {
  int image_index = 0;
  while (file_exists(get_image_path(image_index))) {
    Mat image = imread(get_image_path(image_index), 0);
    image_index++;
  }
  return 0;
}
