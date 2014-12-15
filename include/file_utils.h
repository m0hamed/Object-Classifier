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

using std::string;

bool file_exists(string);

string get_image_path(int);

string get_sift_file_path(int);

#endif
