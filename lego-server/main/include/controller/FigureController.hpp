// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>

#include "./common/Logger.hpp"
#include "./data/FigureHtmlRepository.hpp"

/**
 * @brief Controller for functionality related to Figures.
 */
class FigureController {
 public:
  std::string getFigureByName(const std::string &name) const;

 private:
  FigureHtmlRepository figureRepository{};
};
