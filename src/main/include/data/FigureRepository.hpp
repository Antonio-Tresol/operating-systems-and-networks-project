// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>

#include "model/Figure.hpp"
#include "net/HttpsClient.hpp"

class FigureRepository {
 public:
  Figure findByName(std::string name);
 private:
  static constexpr char HOST[]{"os.ecci.ucr.ac.cr"};
  static constexpr char FIGURE_URL[]{"GET /lego/list.php?figure="};
};
