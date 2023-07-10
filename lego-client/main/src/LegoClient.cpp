// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include <string>

#include "../../../lego-common/main/include/logging/Logger.hpp"
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
        if (argc < 3) {
            Logger::error("Invalid arguments: Must provide host IP address and figure name.");

            exit(1);
        }

        string hostIpAddr{argv[1]};
        string figureName{argv[2]};

        FigureController(hostIpAddr).printFigureByName(figureName);
    }
    catch (exception const &e) {
        Logger::error("Client has crashed.", e);

        exit(1);
    }

    Logger::info("Finished.");

    exit(0);
}
