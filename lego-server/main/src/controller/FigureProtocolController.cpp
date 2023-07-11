#include "../include/controller/FigureProtocolController.hpp"

#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"
#include "data/FigureHtmlRepository.hpp"
#include "logging/Logger.hpp"
// #include "../../../../lego-common/main/src/net/ProtocolClient.cpp"
#include <filesystem>

using std::string;
using std::vector;
// using std::filesystem;

FigureProtocolController::FigureProtocolController(
    FigureHtmlRepository &figureHtmlRepository)
    : figureHtmlRepository(figureHtmlRepository) {}

FigureProtocolController::~FigureProtocolController() {
  protocolClient.release();
}

void FigureProtocolController::handle(int code, std::string ip,
                                      std::string body) {
  if (code == LEGO_DISCOVER) {
    protocolClient.present(ip, figureHtmlRepository.getAvailableFigures());
  }
}

void FigureProtocolController::presentBcast() {
  protocolClient.presentBcast(figureHtmlRepository.getAvailableFigures());
}
