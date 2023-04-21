// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <functional>
#include <string>
#include <sstream>

#include "./net/socket/Ipv4SslSocket.hpp"

using Handler = std::function<void(const std::string&)>;

/**
 * @brief Makes HTTP requests.
 */
class HttpsServer {
 public:
  HttpsServer();
  /**
   * @brief Makes a GET request to the given resource and host.
   * @param resource Resource to request.
   * @param host Host to request from.
   * @return Response from host.
   */
  [[nodiscard]] std::string get(const std::string &host, const std::string &resource) const;

 private:
  static constexpr char GET[]{"GET "};
  static constexpr char CRLF[]{"\r\n"};
  static constexpr char HOST[]{"Host: "};
  static constexpr char HTTPS[]{"https"};

  Ipv4SslSocket socket{};

  std::map<std::tuple<std::string, std::string>, Handler> routes;
};
