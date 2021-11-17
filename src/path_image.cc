#include "path_image.hpp"

PathImage::PathImage(const GrayscaleImage& image,
                     const ElevationDataset& dataset):
    width_(image.width()), height_(image.height()) {
  // gonna populate image for now . . .
  std::cout << "image width " << image.width() << std::endl;
  std::cout << "image height " << image.height() << std::endl;
  path_image_.resize(height_, std::vector<Color>(width_));
  for (size_t i = 0; i < height_; i++) {
    for (size_t j = 0; j < width_; j++) {
      path_image_.at(i).at(j) = image.color_at(i, j);
    }
  }
  // now I am starting greedy algo . . .
  for (size_t row = 0; row < height_; row++) {
    Path topush = Path(width_, row);
    size_t currentrow = row;
    std::cout << "row of iterator is " << row << std::endl;
    for (size_t col = 0; col < width_; col++) {
      std::cout << "col of iterator is " << col << std::endl;
      topush.set_loc(col, currentrow);
      if (col == width_ - 1) {
        std::cout
            << "reached final column, pushing back and breaking to next row"
            << std::endl;
        paths_.push_back(topush);
        if (topush.ele_change() < paths_.at(best_path_row_).ele_change()) {
          best_path_row_ = row;
        }
        break;
      }
      if (currentrow == 0) {
        // behavior for when starting row is 0
        std::cout << "entering behavior for top row" << std::endl;
        int delest = abs(dataset.datum_at(currentrow, col) -
                         dataset.datum_at(currentrow, col + 1));
        int delebot = abs(dataset.datum_at(currentrow, col) -
                          dataset.datum_at(currentrow + 1, col + 1));
        if (delest <= delebot) {
          std::cout << "found that forward is less than or equal to bot"
                    << std::endl;
          topush.inc_ele_change(delest);
          // currentrow = currentrow;
        } else if (delebot < delest) {
          std::cout << "found that forward is less than middle" << std::endl;
          topush.inc_ele_change(delebot);
          currentrow++;
        }
      } else if (currentrow == height_ - 1) {
        std::cout << "entering behavior for bot row" << std::endl;
        int deleup = abs(dataset.datum_at(currentrow, col) -
                         dataset.datum_at(currentrow - 1, col + 1));
        int delest = abs(dataset.datum_at(currentrow, col) -
                         dataset.datum_at(currentrow, col + 1));
        if (delest <= deleup) {
          std::cout << "found that forward is less than top" << std::endl;
          topush.inc_ele_change(delest);
          // currentrow = currentrow;
        } else if (deleup < delest) {
          std::cout << "found that top is less than forwards" << std::endl;
          topush.inc_ele_change(deleup);
          currentrow--;
        }
      } else {
        // behavior for everything else.
        std::cout << "entering regular behavior" << std::endl;
        int deleup = abs(dataset.datum_at(currentrow, col) -
                         dataset.datum_at(currentrow - 1, col + 1));
        int delest = abs(dataset.datum_at(currentrow, col) -
                         dataset.datum_at(currentrow, col + 1));
        int delebot = abs(dataset.datum_at(currentrow, col) -
                          dataset.datum_at(currentrow + 1, col + 1));
        if (delest <= deleup && delest <= delebot) {
          std::cout << "found that forward is less than bot and top"
                    << std::endl;
          topush.inc_ele_change(delest);
          // currentrow = currentrow;
        } else if (delebot < delest && delebot <= deleup) {
          std::cout << "found that bot is less than forwards and top"
                    << std::endl;
          topush.inc_ele_change(delebot);
          currentrow++;
        } else if (deleup < delest && deleup < delebot) {
          std::cout << "found that top is less then forwards and bot"
                    << std::endl;
          topush.inc_ele_change(deleup);
          currentrow--;
        }
      }
    }
  }

  std::cout << "made it out of making paths, now have to draw them . . ."
            << std::endl;
  // now I am going to change the image so that the red paths are traced . . .
  for (size_t row = 0; row < height_; row++) {
    std::cout << "row is " << row << std::endl;
    for (size_t col = 0; col < width_; col++) {
      std::cout << "col is " << col << std::endl;
      size_t rowinpath = paths_.at(row).path().at(col);
      path_image_.at(rowinpath).at(col) = Color(252, 25, 63);
    }
  }
  // GREEN PATH
  for (size_t col = 0; col < width_; col++) {
    size_t rowinpath = paths_.at(best_path_row_).path().at(col);
    path_image_.at(rowinpath).at(col) = Color(31, 253, 13);
  }
}

void PathImage::to_ppm(const std::string& name) const {
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
      ofs << path_image_.at(row).at(col).red() << " "
          << path_image_.at(row).at(col).green() << " "
          << path_image_.at(row).at(col).blue() << " ";
    }
  }
  ofs << std::endl;
}