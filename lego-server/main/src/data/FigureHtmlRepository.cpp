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
#include <vector>

using std::string;
using std::vector;
 
FigureHtmlRepository::FigureHtmlRepository() {
  struct stat sb;
  if (stat(getResourcePath().c_str(), &sb) == -1) {
    throw std::runtime_error("Resource directory not found");
  }

  availableFigures = findAllHtmlFiles();
}

string FigureHtmlRepository::findByName(const string& name) const {

  string filenameStr{getResourcePath().c_str()};
  filenameStr += "/" + name + ".html";

  struct stat sb;
  if (!std::filesystem::exists(filenameStr)) {
    throw std::invalid_argument("Resource file not found");
  }

  std::ifstream figureFile(filenameStr);
  std::stringstream buffer;
  buffer << figureFile.rdbuf();
  figureFile.close();
  return buffer.str();
}

vector<string> FigureHtmlRepository::findAllHtmlFiles() {
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

std::filesystem::path FigureHtmlRepository::getResourcePath() const {
  std::filesystem::path currentFilePath(__FILE__);
  std::filesystem::path rootPath = currentFilePath.parent_path();
  std::filesystem::path resRootPath = (rootPath.parent_path()).parent_path();
  resRootPath = resRootPath.parent_path();
  std::filesystem::path resourcePath = resRootPath / "res";
  return resourcePath;
}

std::vector<std::string> FigureHtmlRepository::getAvailableFigures() const {
    return availableFigures;
}
