// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>
#include <memory>

#include "./logging/Logger.hpp"

/**
 * @brief Controller for functionality related to Figures.
 */
class FigureController {
 public:
  /**
   * @brief Default constructor.
   */
  FigureController();
  /**
   * @brief Returns a figure's HTML by name.
   * @param name Name of figure to get.
   * @return Figure HTML.
   */
  // TODO: necesita tabla de enrutamiento para saber a que servidor ir
    std::string getFigureByName(const std::string &name) const;
  private:
    // std::shared_ptr<std::unordered_map<std::string, std::vector<std::string>>> routingTable;
};

