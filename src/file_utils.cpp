/*
 * =====================================================================================
 *
 *       Filename:  file_utils.cpp
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
#include "file_utils.h"

bool file_exists(string path) {
  if (FILE *file = fopen(path.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

string get_image_path(int image_index) {
  std::stringstream s;
  s << "path/to/image" << image_index << ".png";
  return s.str();
}

string get_sift_file_path(int image_index) {
  std::stringstream s;
  s << "path/to/sift_file" << image_index << ".sift";
  return s.str();
}
