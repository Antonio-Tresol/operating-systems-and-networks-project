#pragma once

#include "../../../../lego-common/main/include/net/socket/IPv4SslSocket.hpp"
#include "../../../../lego-common/main/include/logging/Logger.hpp"
#include <map>
#include <string>
#include <sstream>

class ProxyHttpsController {
  public:
    ProxyHttpsController() = default;
    ~ProxyHttpsController() = default;
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
    * @brief serves the response for the usual clients (web browser and lego
    * clients)
    * @param client socket to send the response
    * @param request request from the client
    */
    void serveFigure(const std::shared_ptr<IPv4SslSocket> &client,
                      const std::string &request);
};