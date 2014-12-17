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
#include <algorithm>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/ml/ml.hpp>
#include <time.h>

#define TRAINING_DATA_SIZE 0.8f

vector<Mat> pick_random_images(vector<Mat>, int);
vector<int> generate_random_numbers(int, int);
vector<Mat> combine_vectors_of_mat(vector<Mat>, vector<Mat>, vector<Mat>);
vector<CvNormalBayesClassifier*> build_classifiers(int, Mat, vector<int>);
double eval_classifier(CvNormalBayesClassifier*, Mat, Mat);

#endif
