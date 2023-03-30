// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#pragma once

#include <string>
#include <vector>

using Row = std::pair<std::string, int>; // description, amount

class Figure {
 public:
  explicit Figure(std::string html);
 private:
  std::string name;
  std::vector<Row> parts;
};