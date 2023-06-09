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
#include <utility>
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
  /**
   * @brief Constructs a server based on a given certificate with key.
   * @param certPath Keyed certificate to use for SSL.
   */
  explicit FigureHttpsServer(const std::string &certPath);

  ~FigureHttpsServer();

  [[noreturn]] void start();

  void stop();

 private:
  static constexpr int NUM_WORKERS{8};
  static constexpr int PORT{7777};
  static constexpr int QUEUE{128};

  static const std::map<std::string, std::string> errorHeaders;

  IPv4SslSocket listener;

  FigureController figureController{};

  Queue<std::shared_ptr<IPv4SslSocket>> clientQueue{};

  std::vector<Worker> workers{};

  /**
   * @brief Worker method to process individual requests.
   */
  void handleRequests();

  /**
   * @brief Returns map of headers for a given HTTP request.
   * @param stream Remainder of HTTP stream.
   * @return Map of headers.
   */
  static std::map<std::string, std::string> parseHeaders(
      std::istringstream &stream);

  /**
   * @brief Returns a map of parts for an HTTP request.
   * @param request HTTP request to build map for.
   * @return Map of HTTP request.
   */
  static std::map<std::string, std::map<std::string, std::string>>
  parseHttpRequest(const std::string &request);

  /**
   * @brief Parses last part of a URL for resource.
   * @param url URL to parse.
   * @return Last portion of URL.
   */
  static std::string getLastPath(const std::string &url);

  /**
   * @brief Confirms whether passed URL is pointing to desired section.
   * @param url URL to confirm.
   * @return Whether URL points to section or not.
   */
  static bool validateUrlFormat(const std::string &url);

  /**
   * @brief Builds an HTTP response.
   * @param statusCode Status code for response.
   * @param body Body for response.
   * @return Response.
   */
  static std::string generateHttpResponse(int statusCode,
                                          const std::string &body);

  /**
   * @brief Builds and sends an HTTP response over a socket.
   * @param client Socket to send response through.
   * @param statusCode Status code for response.
   * @param body Body for response.
   */
  static void sendHttpResponse(const std::shared_ptr<IPv4SslSocket> &client,
                               int statusCode, const std::string &body);

  /**
   * @brief Builds and sends an HTTPS response over a socket.
   * @param client Socket to send response through.
   * @param statusCode Status code for response.
   * @param body Body for response.
   */
  static void sendHttpsResponse(const std::shared_ptr<IPv4SslSocket> &client,
                                int statusCode, const std::string &body);
  /**
   * @brief builds the body of the response for the figures send to nachos
   * client
   * @param string with the html code of the figures
   * @return string with the body of the response
   */
  std::string formatForNachos(const string &html);
  /**
   * @brief checks if the request comes from a nachos client
   */
  bool isNachos(const std::string &request);
  /**
   * @brief serves the response for the nachos client
   * @param client socket to send the response
   * @param request request from the client
   */
  void serveNachos(const std::shared_ptr<IPv4SslSocket> &client,
                   const std::string &request);
  /**
   * @brief serves the response for the usual clients (web browser and lego
   * clients)
   * @param client socket to send the response
   * @param request request from the client
   */
  void serveFigures(const std::shared_ptr<IPv4SslSocket> &client,
                    const std::string &request);
};
