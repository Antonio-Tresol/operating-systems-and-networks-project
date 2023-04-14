// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>

#include "./common/Logger.hpp"
#include "./data/FigureRepository.hpp"
#include "./model/Figure.hpp"

/**
 * @brief Controller for the Figure class.
 */
class FigureController {
 public:
  /**
   * @brief Creates a new FigureController and initializes the
   * FigureRepository to print the figure data.
   * @param name Name of the figure to print.
   */
  void printFigureByName(const std::string &name) const;

 private:
  /**
   * @brief FigureRepository object to print the figure data.
   */
  FigureRepository figureRepository{};
};
