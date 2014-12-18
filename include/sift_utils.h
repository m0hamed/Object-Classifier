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


vector<KeyPoint> create_dense_keypoints(int, int, int);
vector<Mat> get_category_sift_descriptors(const string prefix, const
    vector<string>&);
void create_sift_descs(const string, const string, int*);
void create_bows(const string, const string);
Mat create_vocab(const Mat, const vector<int>, const int, const int);
Mat read_descs(const string, vector<string>&, vector<int>&, int*, int*);
Mat get_histograms(const Mat&, const Mat&, const int);
void write_bows(const string, const string, const Mat&, const vector<string>&,
    const vector<int>&);

#endif
