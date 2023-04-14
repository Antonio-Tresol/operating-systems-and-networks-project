// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>

#include "./common/Logger.hpp"
#include "./model/Figure.hpp"
#include "./data/FigureRepository.hpp"

class FigureController {
public:
    void printFigureByName(const std::string &name) const;

private:
    FigureRepository figureRepository{};
};
