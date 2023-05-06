// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/net/FigureHttpsServer.hpp"

using ::Handler;
using std::exception;
using std::runtime_error;
using std::string;
// TODO: recibir senales de interrupcion para cerrar el server
// Agregar Cola (reutilizar la de Jeisson)
// cerrar el server implica un stop mete en la cola un nullptr
// para que los threads se detengan.
// hacer un join de los threads
FigureHttpsServer::FigureHttpsServer(std::string certificatesFilePath,
                                     int port = 7777) {
  /*
  Server = socket(certs, port)  # constructor debe recibir certificados,
                                # cargarlos, iniciar el contexto, llaves,
                                # hacer bind y hacer listen.
  */
}

/**
 * @brief Inicia el servidor, crea los threads y los pone a correr. Ademas
 * acepta conexiones entrantes y las pone en la cola de clientes.
 */
void FigureHttpsServer::start() {
  /*
  # pone a correr los X threads TODO:
  for thread in threads:
    handlers[thread].push_back(handler(handleRequest))

  while (true):
    socket *client = server.accept()
    clientQueue.enqueue(client)  // recibir request
  */
}
/**
 * @brief Detiene el servidor, cierra el socket y los threads.
 * @details mandar un nullptr a la cola de clientes para que los threads se
 * detengan y hacer un join de los threads
 */

void FigureHttpsServer::stop() {
  /*
  clientQueue.enqueue(nullptr)  # condicion de parada de los threads
  for thread in threads:
     handlers[thread].join()
  */
}

void FigureHttpsServer::handleRequests() {
  /*lee el request del socket */
  /*
 while (true):
  client = clientQueue.dequeue()
   if client == nullptr:
    break
   else:
     client->SSLCreate(this->server)
     client->SSLAccept()
     client->SSLRead(request)
     # Revisa el metodo (GET, POST, PUT, DELETE)
     # Revisa que 'tipo' de path es ("/*")
     # dado que hay que extraer un parametro, lo hace
     params = getUrlParams(request)
     body = figureControler.findByName(map["figure"])
     if body == "":
       response = sendHttpResponse(client, 404, params, body)
     else:
       response = sendHttpResponse(client, 200, params, body)
     close(client)
*/
}

std::map<std::string, std::string> FigureHttpsServer::getUrlParams(
    const std::string& httpRequest) {
  std::map<std::string, std::string> params;
  std::regex urlParamRegex("GET\\s.+\\?(.+)\\sHTTP\\/1\\.1");
  std::smatch urlParamMatch;

  if (std::regex_search(httpRequest, urlParamMatch, urlParamRegex) &&
      urlParamMatch.size() > 1) {
    std::string paramString = urlParamMatch.str(1);
    std::regex paramRegex("([^=&]+)=([^&]+)");
    std::sregex_iterator paramIter(paramString.begin(), paramString.end(),
                                   paramRegex);
    std::sregex_iterator paramEnd;

    while (paramIter != paramEnd) {
      std::smatch match = *paramIter;
      params[match.str(1)] = match.str(2);
      ++paramIter;
    }
  }

  return params;
}

std::string FigureHttpsServer::generateHttpResponse(
    int statusCode, const std::map<std::string, std::string>& headers,
    const std::string& body) {
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

  std::string response =
      "HTTP/1.1 " + std::to_string(statusCode) + " " + statusMessage + "\r\n";
  for (const auto& header : headers) {
    response += header.first + ": " + header.second + "\r\n";
  }
  response += "Content-Length: " + std::to_string(body.size()) + "\r\n";
  response += "\r\n" + body;

  return response;
}

void FigureHttpsServer::sendHttpResponse(
    Ipv4SslSocket* client, int statusCode,
    const std::map<std::string, std::string>& headers,
    const std::string& body) {
  std::string response =
      FigureHttpsServer::generateHttpResponse(statusCode, headers, body);
  // client->SSLWrite(response);
}
