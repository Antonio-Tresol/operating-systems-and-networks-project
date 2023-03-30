// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#pragma once

#include <string>

#include "model/Figure.hpp"

class FigureService {
 public:
  Figure fetchFigure(std::string name);
 private:
  static constexpr char FIGURE_URL[]{"os.ecci.ucr.ac.cr/lego/list.php?figure="};
};