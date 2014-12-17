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
 *         Author:  Mohamed Ashraf (m0hamed)
 *   Organization:  GUC
 *
 * =====================================================================================
 */
#ifndef SIFT_UTILS_H
#define SIFT_UTILS_H

#include "globals.h"

#define DESC_PATH "../sift/"

vector<KeyPoint> create_dense_keypoints(int, int, int);
vector<Mat> get_category_sift_descriptors(const string prefix, const vector<string>&);
void create_sift_descs(const string, int*);

#endif
