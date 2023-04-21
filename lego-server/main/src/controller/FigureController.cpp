// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/controller/FigureController.hpp"

using std::cout;
using std::invalid_argument;
using std::runtime_error;
using std::string;
using std::throw_with_nested;

void FigureController::run() const {
  registerRoutes();

  for(;;) {
    httpsServer.accept();
  }
}

string FigureController::getFigureByName(const string &name) const {
  try {
    string figureHtml{figureRepository.findByName(name)};
    return figureHtml;
  }
  catch(invalid_argument &ia) {
    throw_with_nested(runtime_error("Could not find figure: "));
  }
}

void registerRoutes() {
  server.addRoute("/hello", "GET", std::bind(&Controller::handleHelloRequest, this, std::placeholders::_1));
}
