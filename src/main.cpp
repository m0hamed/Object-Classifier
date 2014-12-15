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

int main() {
  vector<Mat> car_descriptors = get_category_sift_descriptors(CAR_IMAGES_PATH);
  vector<Mat> bike_descriptors = get_category_sift_descriptors(BIKE_IMAGES_PATH);
  vector<Mat> cow_descriptors = get_category_sift_descriptors(COW_IMAGES_PATH);
  return 0;
}
