#ifndef GRAYSCALE_IMAGE_H
#define GRAYSCALE_IMAGE_H

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

class GrayscaleImage {
public:
  // write behavior declarations here; define in grayscale_image.cc.
  // IMPLEMENT
  GrayscaleImage(const ElevationDataset& dataset);
  GrayscaleImage(const std::string& filename, size_t width, size_t height);
  const Color& color_at(int row, int col) const;
  void to_ppm(const std::string& name) const;

  // DEFINED HERE
  size_t width() const { return width_; }
  size_t height() const { return height_; }
  unsigned int max_color_value() const { return max_color_value_; }
  const std::vector<std::vector<Color>>& get_image() const { return image_; }

private:
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> image_;
  static const int max_color_value_ = 255;
};

#endif