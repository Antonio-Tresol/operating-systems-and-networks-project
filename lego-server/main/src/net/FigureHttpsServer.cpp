// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/FigureHttpsServer.hpp"

using std::exception;
using std::runtime_error;
using std::string;
using ::Handler;

FigureHttpsServer::FigureHttpsServer() {
  // create socket ( ipv4SSL socket)
  // bind to port X port 
  // listen to declared socket as server (passive socket)
  // listo
}

void accept() {
  // bucle:
  //  cliente = ssl_accept() // recibir request
  //  Handler (void handleRequest, Socket Cliente, x, y, z) 
  // descompone el string del request (get url params)
  // revisa su validez
  //!! llama handleRequest(path, method)
}

void handleRequest(Ipv4SslSocket* client) {
    /*lee el request del socket */
  // string request{}
  // client->read(request)
    /* Revisa el metodo (GET, POST, PUT, DELETE) */
    /* Revisa que 'tipo' de path es ("/*") */
    /*dado que hay que extraer un parametro, lo hace */
  // params = getURLParams (request) // devuelve un map
  // (str figureName = map["figure"])
  //    res = handler(arg)
  //    resp = buildResp(res)
  //    socketNuevo(returnAddr, resp)
  //    socketNuevo.close
}

std::map<std::string, std::string> getUrlParams(const std::string& httpRequest) {
    std::map<std::string, std::string> params;
    std::regex urlParamRegex("GET\\s.+\\?(.+)\\sHTTP\\/1\\.1");
    std::smatch urlParamMatch;

    if (std::regex_search(httpRequest, urlParamMatch, urlParamRegex) && urlParamMatch.size() > 1) {
        std::string paramString = urlParamMatch.str(1);
        std::regex paramRegex("([^=&]+)=([^&]+)");
        std::sregex_iterator paramIter(paramString.begin(), paramString.end(), paramRegex);
        std::sregex_iterator paramEnd;

        while (paramIter != paramEnd) {
            std::smatch match = *paramIter;
            params[match.str(1)] = match.str(2);
            ++paramIter;
        }
    }

    return params;
}


std::string generateHttpResponse(int statusCode, const std::map<std::string, std::string>& headers, const std::string& body) {
  std::string statusMessage;
  switch (statusCode) {
    case 200:
      statusMessage = "OK";
      break;
    case 404:
      statusMessage = "Not Found";
      break;
      // Add other status codes and messages as needed
    default:
      statusMessage = "Unknown";
  }

  std::string response = "HTTP/1.1 " + std::to_string(statusCode) + " " + statusMessage + "\r\n";
  for (const auto& header : headers) {
    response += header.first + ": " + header.second + "\r\n";
  }
  response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
  response += "\r\n" + body;

  return response;
}

void sendHttpResponse(SSL* ssl, int statusCode, const std::map<std::string, std::string>& headers, const std::string& body) {
  std::string response = generateHttpResponse(statusCode, headers, body);
  SSL_write(ssl, response.c_str(), response.size());
}
