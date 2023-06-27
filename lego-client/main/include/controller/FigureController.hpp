// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>

#include "../../../../lego-common/main/include/logging/Logger.hpp"
#include "./data/FigureRepository.hpp"
#include "./model/Figure.hpp"

/**
 * @brief Controller for functionality related to Figures.
 */
class FigureController {
 public:
  /**
   * @brief Prints a Figure obtained from the repository by name.
   * @param name Name of the figure to print.
   */
  void printFigureByName(const std::string &name) const;

 private:
  FigureRepository figureRepository{};
};
