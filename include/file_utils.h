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

#define IMAGES_PATH_PREFIX "../images/"
#define CAR_IMAGES_PATH (string(IMAGES_PATH_PREFIX) + "cars/")

bool file_exists(string);

vector<string> get_files_in_directory(string);

#endif
