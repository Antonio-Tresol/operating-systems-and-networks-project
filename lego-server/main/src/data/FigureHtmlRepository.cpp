// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/data/FigureHtmlRepository.hpp"

using std::string;

FigureHtmlRepository::FigureHtmlRepository() {
  // NOTA: Usar <filesystem> para manejar directiorios
  // Revisar si existe figurePath, si no construirlo
  // Revisar si se encuentran donde se esperaria las figuras del repo
  // Si se encuentran ahi, copiarlas al figurePath
}

string FigureHtmlRepository::findByName(const string& name) const {
 // matchear name al nombre de algun archivo html y retornar
}

std::filesystem::path getResourcePath() {
  std::filesystem::path currentFilePath(__FILE__);
  std::filesystem::path repoRoot = currentFilePath.parent_path();
  std::filesystem::path resourcePath = repoRoot / "res";
  return resourcePath;
}