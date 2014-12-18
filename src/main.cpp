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

int main(int argc, char** argv) {

  int step;
  if (argc <  2)
    step = 0;
  else if (argc == 2)
    step = std::stoi(argv[1]);
  else {
    cout << "usage: ./clasifier [step]" << endl;
    return 1;
  }

  if (step > 2) {
    build_classifiers(BOW_PATH);
  } else if (step > 1) {
    create_bows(DESC_PATH, BOW_PATH);
    build_classifiers(BOW_PATH);
  } else {
    create_sift_descs(IMAGES_PATH, DESC_PATH);
    create_bows(DESC_PATH, BOW_PATH);
    build_classifiers(BOW_PATH);
  }
  return 0;
}
