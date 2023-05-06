// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../../include/data/FigureHtmlRepository.hpp"
#include <sys/stat.h>
#include <filesystem>
#include <stdexcept>
#include <fstream>
#include <iostream>
using std::string;
 
FigureHtmlRepository::FigureHtmlRepository() {
  // NOTA: Usar <filesystem> para manejar directiorios
  // Revisar si existe figurePath, si no construirlo
  // Revisar si se encuentran algo
  // Si se encuentran ahi, copiarlas al figurePath
  struct stat sb;
  if (stat(getResourcePath().c_str(), &sb) == -1) {
    throw std::runtime_error("Resource directory not found");
  }
}

string FigureHtmlRepository::findByName(const string& name) const {
 // matchear name al nombre de algun archivo html y retornar
  string filenameStr{getResourcePath().c_str()};
  filenameStr += "/" + name + ".html";
  struct stat sb;
  // if (stat(filenameStr.c_str(), &sb) == 0 && !(sb.st_mode & S_IFDIR)){
  //   throw std::invalid_argument("Resource file not found");
  // }
  if (!std::filesystem::exists(filenameStr)) {
    throw std::invalid_argument("Resource file not found");
  }
  std::ifstream figureFile(filenameStr);
  std::stringstream buffer;
  buffer << figureFile.rdbuf();
  figureFile.close();
  return buffer.str();

}

std::filesystem::path FigureHtmlRepository::getResourcePath() const {
  std::filesystem::path currentFilePath(__FILE__);
  std::filesystem::path rootPath = currentFilePath.parent_path();
  std::filesystem::path resRootPath = (rootPath.parent_path()).parent_path();
  resRootPath = resRootPath.parent_path();
  std::filesystem::path resourcePath = resRootPath / "res";
  return resourcePath;
}
