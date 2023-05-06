// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <functional>
#include <map>
#include <regex>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include "../common/Queue.hpp"
#include "../controller/FigureController.hpp"
#include "./socket/Ipv4SslSocket.hpp"

// using Handler = std::function<void(const std::string&)>;
using Handler = std::thread;
/**
 * @brief Makes HTTP requests.
 */
class FigureHttpsServer {
 public:
  FigureHttpsServer(std::string certificatesFilePath, int port = 7777);
  /**
   * @brief Makes a GET request to the given resource and host.
   * @param resource Resource to request.
   * @param host Host to request from.
   * @return Response from host.
   */
  [[nodiscard]] std::string get(const std::string& host,
                                const std::string& resource) const;

  void start();
  void stop();

 private:
  static constexpr char GET[]{"GET "};
  static constexpr char CRLF[]{"\r\n"};
  static constexpr char HOST[]{"Host: "};
  static constexpr char HTTPS[]{"https"};
  Ipv4SslSocket server{};
  FigureController figureController{};
  Queue<Ipv4SslSocket*> clientQueue{};
  std::vector<Handler*> handlers{};
  void handleRequests();
  std::map<std::string, std::string> getUrlParams(
      const std::string& httpRequest);
  std::string FigureHttpsServer::generateHttpResponse(
      int statusCode, const std::map<std::string, std::string>& headers,
      const std::string& body);
  void sendHttpResponse(Ipv4SslSocket* client, int statusCode,
                        const std::map<std::string, std::string>& headers,
                        const std::string& body);
};
