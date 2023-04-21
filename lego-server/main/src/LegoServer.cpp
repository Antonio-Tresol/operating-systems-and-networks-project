// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include <string>

#include "./common/Logger.hpp"
#include "./controller/FigureController.hpp"

using std::exception;
using std::invalid_argument;
using std::out_of_range;
using std::stoi;
using std::string;

/**
 * @brief Entry point.
 */
int main(int argc, char *argv[]) {
    Logger::initialize();
    try {
      FigureController().start();
    }
    catch (exception const &e) {
        Logger::error("Server has crashed.", e);

        exit(1);
    }

    Logger::info("Exiting.");

    exit(0);
}
