#ifndef ELEVATION_DATASET_H
#define ELEVATION_DATASET_H

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

class ElevationDataset {
public:
  // write behavior declarations here; define in elevation_dataset.cc.

  ElevationDataset(const std::string& filename, size_t width, size_t height);
  size_t width() const { return width_; }
  size_t height() const { return height_; }
  int max_ele() const { return max_ele_; }
  int min_ele() const { return min_ele_; }
  int datum_at(size_t row, size_t col) const { return data_.at(row).at(col); }
  const std::vector<std::vector<int>>& get_data() const { return data_; }

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<int>> data_;
  int max_ele_;
  int min_ele_;
};

#endif