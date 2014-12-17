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

using cv::FileStorage;

bool file_exists(string path) {
  if (FILE *file = fopen(path.c_str(), "r")) {
    fclose(file);
    return true;
  } else {
    return false;
  }
}

vector<string> get_files_in_directory(string path) {
  DIR *dir;
  struct dirent *ent;
  vector<string> files;
  if ((dir = opendir(path.c_str())) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir(dir)) != NULL) {
      if (ent->d_name[0] != '.') { // remove hidden files
        files.push_back(ent->d_name);
      }
    }
    closedir(dir);
  }
  return files;
}

void write_file(const string file_path, const Mat& data, const string tag) {
  FileStorage fs(file_path, FileStorage::WRITE);
  fs << tag << data;
  fs.release();
}

void read_file(const string file_path, const string tag, Mat& data) {
  FileStorage fs;
  fs.open(file_path, FileStorage::READ);
  if (!fs.isOpened()) {
    std::cerr << "Failed to open file: " << file_path << endl;
    return;
  }
  fs[tag] >> data;
  fs.release();
}

void read_meta(const string file_path, const string tag, int* rows, int* cols) {
  FileStorage fs;
  fs.open(file_path, FileStorage::READ);
  if (!fs.isOpened()) {
    std::cerr << "Failed to open file: " << file_path << endl;
    return;
  }
  fs[tag]["rows"] >> *rows;
  fs[tag]["cols"] >> *cols;
  fs.release();
}
