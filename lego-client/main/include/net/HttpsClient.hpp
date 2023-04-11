// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>

#pragma once

#include <string>
#include <sstream>

#include "./net/socket/Ipv4SslSocket.hpp"
/**
 * @brief HttpsClient class to make HTTPS requests
 * and get the response.
 */
class HttpsClient {
 public:
  /**
   * @brief Makes a GET request to the given URL and host.
   * @param url URL to make the request.
   * @param host Host to make the request.
   * @return Response of the request.
   */
  [[nodiscard]] std::string get(const std::string &url, const std::string &host) const;

 private:
  // request constants
  static constexpr char GET[]{"GET / HTTP/1.1\r\n"};  // Get request
  static constexpr char HOST[]{"Host: "};  // Host header
  static constexpr char CRLF[]{"\r\n\r\n"};  // End of request (html format)
  static constexpr char HTTPS[]{"https"};  // HTTPS protocol
};
