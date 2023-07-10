// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>

#include "./logging/Logger.hpp"
#include "../data/FigureHtmlRepository.hpp"

/**
 * @brief Ssl controller for functionality related to Figures.
 */
class FigureSslController {
public:
    /**
     * @brief Returns a figure's HTML by name.
     * @param name Name of figure to get.
     * @return Figure HTML.
     */
    std::string getFigureByName(const std::string &name) const;

private:
    FigureHtmlRepository figureRepository{};
};
