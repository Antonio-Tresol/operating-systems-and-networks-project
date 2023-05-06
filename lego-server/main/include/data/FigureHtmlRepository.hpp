// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>
#include <filesystem>
/**
 * @brief Repository of Figure objects.
 */
class FigureHtmlRepository {
 public:
  FigureHtmlRepository();

  std::string findByName(const std::string& name) const;

 private:
  std::filesystem::path getResourcePath() const;
  static constexpr char RES[]{"res"};
};
