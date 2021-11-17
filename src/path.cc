#include "path.hpp"

// constructor first

Path::Path(size_t length, size_t starting_row):
    length_(length),
    starting_row_(starting_row),
    path_(std::vector<size_t>(length)) {}

void Path::set_loc(size_t col, size_t row) { path_.at(col) = row; }

void Path::inc_ele_change(unsigned int value) { ele_change_ += value; }