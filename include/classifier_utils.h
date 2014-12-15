/*
 * =====================================================================================
 *
 *       Filename:  sift_utils.h
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
#ifndef CLASSIFIER_UTILS_H
#define CLASSIFIER_UTILS_H

#include "globals.h"
vector<Mat> pick_random_images(vector<Mat>, int);
vector<int> generate_random_numbers(int, int);

#endif
