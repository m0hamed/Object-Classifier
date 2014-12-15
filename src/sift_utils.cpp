/*
 * =====================================================================================
 *
 *       Filename:  sift_utils.cpp
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

#include "sift_utils.h"

vector<KeyPoint> create_dense_keypoints(int rows, int cols, int grid_size) {
  vector<KeyPoint> points;
  for (int i=0; i<rows; i += grid_size) {
    for (int j=0; j<cols; j += grid_size) {
      points.push_back(KeyPoint(i, j, grid_size));
    }
  }
  return points;
}

