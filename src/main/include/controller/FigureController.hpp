// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.Agrega HttpsClient.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#pragma once

#include <iostream>
#include <string>

#include "common/Logger.hpp"
#include "model/Figure.hpp"
#include "data/FigureRepository.hpp"

class FigureController {
public:
    void printFigureByName(const std::string &name) const;

private:
    FigureRepository figureRepository{FigureRepository()};
};

void FigureController::printFigureByName(const std::string &name) const {
    // TODO: Catch individual exception types.
    Figure figure{figureRepository.findByName(name)};
    std::cout << figure;
}
