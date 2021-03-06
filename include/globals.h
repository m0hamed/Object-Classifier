/*
 * =====================================================================================
 *
 *       Filename:  globals.h
 *
 *    Description:  global constants and includes
 *
 *        Version:  1.0
 *        Created:  12/15/2014 11:37:05 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Mohamed Ashraf (m0hamed), Hossam Ahmed (hossam-mossalam),
 *         Samy Shehata (sshihata)
 *   Organization:  GUC
 *
 * =====================================================================================
 */
#ifndef GLOBALS_H
#define GLOBALS_H

#define VOCAB_ITEMS_PER_CATEGORY 25
#define CENTROIDS_COUNT 100
#define EPSILON 0.1
#define ITERATIONS 100
#define ATTEMPTS 1

#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/nonfree/features2d.hpp>
#include <string>

using std::cout;
using std::flush;
using std::endl;
using std::vector;
using std::string;
using cv::Mat;
using cv::KeyPoint;

#endif
