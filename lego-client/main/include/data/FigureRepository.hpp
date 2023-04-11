// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>

#pragma once

#include <string>

#include "./model/Figure.hpp"
#include "./net/HttpsClient.hpp"

class FigureRepository {
 public:
  [[nodiscard]] Figure findByName(const std::string& name) const;
 private:
  static constexpr char HOST[]{"redes.ecci"};
  static constexpr char URL_TEMPLATE[]{"os.ecci.ucr.ac.cr/lego/list.php?figure="};

  HttpsClient httpsClient{};
};
