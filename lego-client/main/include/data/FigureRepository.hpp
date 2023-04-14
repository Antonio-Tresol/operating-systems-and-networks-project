// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>

#include "./model/Figure.hpp"
#include "./net/HttpsClient.hpp"

/**
 * @brief Repository for the Figure class.
 */
class FigureRepository {
 public:
  /**
   * @brief Finds a figure by its name in the host service.
   * @param name Name of the figure to find.
   * @return Figure with the given name.
   */
  [[nodiscard]] Figure findByName(const std::string& name) const;
 private:
  static constexpr char HOST[]{"os.ecci.ucr.ac.cr"};
  static constexpr char URL_TEMPLATE[]{"/lego/list.php?figure="};

  HttpsClient httpsClient{};
};
