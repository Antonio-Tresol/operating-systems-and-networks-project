#include "../include/controller/FigureProtocolController.hpp"
#include "../../../../lego-common/main/include/net/ProtocolHeader.hpp"
// #include "../../../../lego-common/main/src/net/ProtocolClient.cpp"
#include <filesystem>

using std::vector;
using std::string;
// using std::filesystem;

std::filesystem::path getResourcePath();

FigureProtocolController::FigureProtocolController(int port) : protocolClient(port) {
  this->availableFigures = findAllHtmlFiles();
}

void FigureProtocolController::handle(int code, std::string ip, std::string body) {
  /* 
  Aqui solo me puede llegar un discover (debo enviar mis piezas), porque soy el servidor de piezas como tal,
  yo no handleo present, request, response, release (cuando se mata el servidor),
  ni error (ssl).
  */
//  if (code == LEGO_DISCOVER) {
//    auto itr = availableFigures.begin();
//    string figures = "";
//   while (itr != availableFigures.end()) {
//     figures += itr->first + SEPARATOR;
//     itr++;
//   }
//   const string ipSend = ip;
//   protocolClient.present((&ipSend), this->availableFigures->second);
//  } 
  if (code == LEGO_DISCOVER) {
    // auto itr = availableFigures.begin();
    // std::vector<std::string> figures;
    // while (itr != availableFigures.end()) {
    //   figures.push_back(itr->first);
    //   itr++;
    // }
    

    protocolClient.present(ip, this->availableFigures);
    
  } 

}

vector<string> FigureProtocolController::findAllHtmlFiles() {
    std::vector<std::string> filenames;
    std::string pathStr{getResourcePath().c_str()};

    for (const auto &entry : std::filesystem::directory_iterator(pathStr)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (entry.path().extension() == ".html") {
                // Remove the extension from the filename
                filename = filename.substr(0, filename.size() - 5);
                filenames.push_back(filename);
            }
        }
    }

    return filenames;
}

std::filesystem::path getResourcePath() {
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
