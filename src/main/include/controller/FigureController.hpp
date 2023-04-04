// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#pragma once

#include <iostream>
#include <string>

#include "common/Logger.hpp"
#include "model/Figure.hpp"
#include "net/HttpsClient.hpp"

class FigureController {
public:
    Figure printFigureByName(const std::string &name);

private:
    static const std::string URL_TEMPLATE;
    static const std::string HOST;

    HttpsClient httpClient{HttpsClient()};
};

const std::string FigureController::URL_TEMPLATE{"os.ecci.ucr.ac.cr/lego/list.php?figure={}"};
const std::string FigureController::HOST{"redes.ecci"};

Figure FigureController::printFigureByName(const std::string &name) {
    std::string url{URL_TEMPLATE + name};
    std::string html{httpClient.get(url, HOST)};

    Figure figure{html};

    std::cout << figure;
}
