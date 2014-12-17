/*
 * =====================================================================================
 *
 *       Filename:  file_utils.h
 *
 *    Description:  A collection of helper functions related to file operations
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
#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include "globals.h"
#include <string>
#include <opencv2/core/core.hpp>
#include <dirent.h>

#define IMAGES_PATH "../images/"
#define DESC_PATH "../sift/"
#define BOW_PATH "../bow/"

bool file_exists(string);
vector<string> get_files_in_directory(string);
void write_file(const string, const Mat&, const string);
void read_file(const string, const string, Mat& );
void read_meta(const string, const string, int*, int*);

#endif
