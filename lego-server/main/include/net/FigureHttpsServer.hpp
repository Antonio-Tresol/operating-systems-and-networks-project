// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <functional>
#include <string>
#include <sstream>
#include <map>
#include <regex>
#include <thread>

#include "./socket/Ipv4SslSocket.hpp"
#include "../controller/FigureController.hpp"

// using Handler = std::function<void(const std::string&)>;
using Handler = std::jthread;
/**
 * @brief Makes HTTP requests.
 */
class FigureHttpsServer {
 public:
  FigureHttpsServer();
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
  static constexpr char HTTPS[]{"https"};
  Ipv4SslSocket socket{};
  FigureController figureController{};

  std::string generateHttpResponse(int statusCode, std::string& headers, 
    const std::string& body);

};
