#ifndef PATH_IMAGE_H
#define PATH_IMAGE_H

#include <cstdlib>  // for size_t
#include <string>
#include <vector>

#include "color.hpp"
#include "grayscale_image.hpp"
#include "path.hpp"

class PathImage {
public:
  // write behavior declarations here; define in path_image.cc.

  // IMPLEMENT THESE . . .
  PathImage(const GrayscaleImage& image, const ElevationDataset& dataset);
  void to_ppm(const std::string& name) const;

  // THESE FUNCTIONS DOWN HERE ARE DONE . . .
  size_t width() const { return width_; }
  size_t height() const { return height_; }
  unsigned int max_color_value() const { return max_color_value_; }
  const std::vector<Path>& paths() const { return paths_; }
  const std::vector<std::vector<Color>>& path_image() const {
    return path_image_;
  }

private:
  std::vector<Path> paths_;
  size_t width_;
  size_t height_;
  std::vector<std::vector<Color>> path_image_;
  static const int max_color_value_ = 255;
  // CAN ADD THIS IF I WANT
  int best_path_row_ = 0;
};

#endif