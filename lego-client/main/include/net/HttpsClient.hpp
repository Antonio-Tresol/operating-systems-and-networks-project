// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <sstream>
#include <string>

#include "./net/socket/Ipv4SslSocket.hpp"
/**
 * @brief Makes HTTP requests.
 */
class HttpsClient {
 public:
  /**
   * @brief Makes a GET request to the given resource and host.
   * @param resource Resource to request.
   * @param host Host to request from.
   * @return Response from host.
   */
  [[nodiscard]] std::string get(const std::string &host,
                                const std::string &resource) const;

 private:
  static constexpr char GET[]{"GET "};
  static constexpr char CRLF[]{"\r\n"};
  static constexpr char HOST[]{"Host: "};
  static constexpr int PORT{7777};
};
