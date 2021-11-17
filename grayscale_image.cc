#include "grayscale_image.hpp"

const Color& GrayscaleImage::color_at(int row, int col) const {
  return image_.at(row).at(col);
}

GrayscaleImage::GrayscaleImage(const ElevationDataset& dataset):
    width_(dataset.width()), height_(dataset.height()) {
  image_.resize(height_, std::vector<Color>(width_));
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      if (dataset.min_ele() == dataset.max_ele()) {
        std::cout << "adding black because max = min for this dataset"
                  << std::endl;
        Color black = Color();
        image_.at(i).at(j) = black;
      } else {
        // float tester =
        //((255.00 *
        // float((dataset.datum_at(i, j)) - float(dataset.min_ele())) /
        // (float(dataset.max_ele()) - float(dataset.min_ele()))));
        int shade_of_grey = std::round(
            (255.00 *
             float((dataset.datum_at(i, j)) - float(dataset.min_ele())) /
             (float(dataset.max_ele()) - float(dataset.min_ele()))));
        // std::cout << "adding: " << shade_of_grey << " " << tester <<
        // std::endl;
        Color colorAtElevation =
            Color(shade_of_grey, shade_of_grey, shade_of_grey);
        image_.at(i).at(j) = colorAtElevation;
      }
    }
  }
}

GrayscaleImage::GrayscaleImage(const std::string& filename,
                               size_t width,
                               size_t height):
    width_(width), height_(height) {
  image_.resize(height_, std::vector<Color>(width_));
  ElevationDataset mydata = ElevationDataset(filename, width_, height_);
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      if (mydata.min_ele() == mydata.max_ele()) {
        std::cout << "adding black because max = min for this dataset"
                  << std::endl;
        Color black = Color();
        image_.at(i).at(j) = black;
      } else {
        int shade_of_grey = std::round(
            (255.00 * (float(mydata.datum_at(i, j)) - float(mydata.min_ele())) /
             (float(mydata.max_ele()) - float(mydata.min_ele()))));
        // std::cout << "adding: " << shade_of_grey << std::endl;
        Color colorAtElevation =
            Color(shade_of_grey, shade_of_grey, shade_of_grey);
        Color(shade_of_grey, shade_of_grey, shade_of_grey);
        image_.at(i).at(j) = colorAtElevation;
      }
    }
  }
}

void GrayscaleImage::to_ppm(const std::string& name) const {
  std::ofstream ofs{name};
  if (!ofs.is_open()) {
    throw std::runtime_error("file not opening in toppm and something is bad");
  }
  ofs << "P3" << std::endl
      << std::to_string(width_) << " " << std::to_string(height_) << std::endl
      << std::to_string(max_color_value_);
  for (size_t row = 0; row < height_; row++) {
    ofs << std::endl;
    for (size_t col = 0; col < width_; col++) {
      ofs << color_at(row, col).blue() << " " << color_at(row, col).red() << " "
          << color_at(row, col).green() << " ";
    }
  }
  ofs << std::endl;
}
