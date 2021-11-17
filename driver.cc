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
#include "path_image.hpp"

int main() {
  ElevationDataset testing = ElevationDataset(
      "example-data/ex_input_data/map-input-w480-h480.dat", 480, 480);

  for (size_t i = 0; i < testing.height(); i++) {
    std::cout << std::endl;
    for (size_t j = 0; j < testing.width(); j++) {
      std::cout << testing.datum_at(i, j);
    }
  }
  std::cout << std::endl;
  std::cout << testing.max_ele() << " " << testing.min_ele() << std::endl;
  GrayscaleImage testingImage = GrayscaleImage(testing);
  testingImage.to_ppm("something.ppm");

  PathImage testpathim = PathImage(testingImage, testing);
  for (size_t i = 0; i < testing.height(); i++) {
    std::cout << std::endl;
    std::cout << "path " << i << ":  ";
    for (size_t j = 0; j < testing.width(); j++) {
      std::cout << testpathim.paths().at(i).path().at(j) << " ";
    }
  }
  for (size_t i = 0; i < testing.height(); i++) {
    std::cout << std::endl;
    for (size_t j = 0; j < testing.width(); j++) {
      std::cout << testpathim.path_image().at(i).at(j).red() << " ";
    }
  }
  testpathim.to_ppm("example-data/ex_output_grayscale/output.ppm");
}