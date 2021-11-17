#include "elevation_dataset.hpp"

ElevationDataset::ElevationDataset(const std::string& filename,
                                   size_t width,
                                   size_t height):
    width_(width), height_(height) {
  max_ele_ = INT32_MIN;  // the lowest this num will go
  min_ele_ = INT32_MAX;  // the max
  data_.resize(height_, std::vector<int>(width_));
  // WILL CHECK NUMBER OF ENTRIES FIRST AND CONFIRM IT IS EQUAL TO WIDTH *
  // HEIGHT
  std::ifstream testdata{filename};
  if (!testdata.is_open()) {
    throw std::runtime_error(
        "file didn't open for test and something is fucked");
  }
  size_t count = 0;
  int totrash;
  std::string totrash1;
  while (testdata >> totrash) {
    // my count here is one off because it is reading new line thingy at end of
    // file . . . how do I check what last element is in file?
    count++;
  }

  if (count != width_ * height_) {
    std::cout << count << " does not equal " << width_ * height_ << std::endl;
    throw std::runtime_error("width and height dont match with total size");
  }
  std::cout << "count is " << count << std::endl;
  // ACTUAL WORK STARTS
  std::ifstream mydata{filename};
  if (!mydata.is_open()) {
    throw std::runtime_error("file didn't open and something is fucked");
  }
  for (size_t row = 0; row < height_; row++) {
    for (size_t col = 0; col < width_; col++) {
      if (mydata.good()) {
        mydata >> data_.at(row).at(col);
        if (data_.at(row).at(col) > max_ele_) {
          max_ele_ = data_.at(row).at(col);
        }
        if (data_.at(row).at(col) < min_ele_) {
          min_ele_ = data_.at(row).at(col);
        }
      } else {
        throw std::runtime_error("Format read error");
      }
    }
  }
}

// gotta watch video on validating user inputs to see what to do about bad
// inputs/how to check length of file etc