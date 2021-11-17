#ifndef PATH_H
#define PATH_H

#include <cassert>
#include <cmath>
#include <cstdlib>  // for size_t
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

#include "color.hpp"
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"

class Path {
public:
  // write behavior declarations here; define in path.cc.
  Path(size_t length, size_t starting_row);
  size_t length() const { return length_; }
  size_t starting_row() const { return starting_row_; }
  unsigned int ele_change() const { return ele_change_; }
  void inc_ele_change(
      unsigned int value);  // increments elevation change by
                            // some positive value, the one greedy chooses
  const std::vector<size_t>& path() const {
    return path_;
  }  // have to ask in office hours about this . . . is this returning a
     // reference or copy???
  void set_loc(size_t col, size_t row);
  void set_row(size_t row) { starting_row_ = row; }

private:
  size_t length_;
  size_t starting_row_;
  std::vector<size_t> path_;
  unsigned int ele_change_ = 0;
};

#endif