#include "../include/controller/FigureProtocolController.hpp"
#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"
#include "data/FigureHtmlRepository.hpp"
// #include "../../../../lego-common/main/src/net/ProtocolClient.cpp"
#include <filesystem>

using std::vector;
using std::string;
// using std::filesystem;

FigureProtocolController::FigureProtocolController(FigureHtmlRepository &figureHtmlRepository) :
        figureHtmlRepository(figureHtmlRepository) {}


FigureProtocolController::~FigureProtocolController() {
    protocolClient.release();
}

void FigureProtocolController::handle(int code, std::string ip, std::string body) {
  if (code == LEGO_DISCOVER) {
    protocolClient.present(ip, figureHtmlRepository.getAvailableFigures());
  } 

}

void FigureProtocolController::presentBcast() {
    protocolClient.presentBcast(figureHtmlRepository.getAvailableFigures());
}

std::filesystem::path FigureProtocolController::getResourcePath() {
  // std::filesystem::path currentFilePath(__FILE__);
  // std::filesystem::path rootPath = currentFilePath.parent_path();
  // std::filesystem::path resRootPath = (rootPath.parent_path()).parent_path();
  // resRootPath = resRootPath.parent_path();
  // std::filesystem::path resourcePath = resRootPath / "res";
  // return resourcePath;

  std::filesystem::path currentFilePath(std::filesystem::current_path());

  std::filesystem::path rootPath = currentFilePath.parent_path();
  std::filesystem::path resRootPath = (rootPath.parent_path()).parent_path();
  std::filesystem::path resourcePath = resRootPath / "res";
  return resourcePath;
}
