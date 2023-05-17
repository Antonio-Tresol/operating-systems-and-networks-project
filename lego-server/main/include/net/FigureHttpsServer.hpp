// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <functional>
#include <map>
#include <memory>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "../common/Queue.hpp"
#include "../controller/FigureController.hpp"
#include "./socket/IPv4SslSocket.hpp"

using Worker = std::thread;

/**
 * @brief Makes HTTP requests.
 */
class FigureHttpsServer {
 public:
  ~FigureHttpsServer();

  [[noreturn]] void start();

  void stop();

 private:
  static constexpr int PORT{7777};
  static constexpr int QUEUE{128};
  static constexpr char CERT_PATH[]{"../ci0123.pem"};
  static constexpr char FIGURE[]{"figure"};

  IPv4SslSocket listener{CERT_PATH, CERT_PATH};

  FigureController figureController{};

  Queue<std::shared_ptr<IPv4SslSocket>> clientQueue{};

  std::vector<Worker> workers{};

  void handleRequests();

  std::map<std::string, std::string> parseHeaders(std::istringstream &stream);

  std::map<std::string, std::map<std::string, std::string>> parseHttpRequest(
      const std::string &request);

  static std::string getLastPath(const std::string &url);

  static std::string generateHttpResponse(
      int statusCode, const std::map<std::string, std::string> &headers,
      const std::string &body);

  static void sendHttpResponse(
      const std::shared_ptr<IPv4SslSocket> &client, int statusCode,
      const std::map<std::string, std::string> &headers,
      const std::string &body);
};
