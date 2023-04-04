// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using Row = std::pair<std::string, int>; // description, amount

class Figure {
 public:
  explicit Figure(const std::string &html);

  friend std::ostream& operator<<(std::ostream& os, const Figure& figure);

 private:
  std::string name;
  std::vector<Row> parts;
};

Figure::Figure(const std::string &html) {
    // TODO
}

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    std::string asString{" ? "}; // TODO
    return os << asString;
}
