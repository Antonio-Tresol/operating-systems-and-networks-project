// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/controller/FigureController.hpp"

using std::cout;
using std::string;

void FigureController::printFigureByName(const string &name) const {
    Figure figure{figureRepository.findByName(name)};

    if (figure.name.empty() || figure.parts.empty()) {
        Logger::error("Figure is empty, cannot print.");
    } else {
        Logger::info(string(figure));
    }
}

FigureController::FigureController(const std::string &host) : figureRepository(host) {}
