// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../../include/net/ProtocolServer.hpp"
#include "../../include/net/ProtocolHeader.hpp"
#include <arpa/inet.h>

#define RESPOND_ERROR -2
#define THREAD_AMOUNT 7

ProtocolServer::ProtocolServer(int port) : receiverSocket(port),
                                           keepListeningFlag(true)
{
}

void ProtocolServer::keepListening() const {
  // Loop for listening (receiving)
  // TODO: check if the socket is binded.
  while (keepListeningFlag) {
    std::string message = this->receiverSocket.receive(); // TODO: thread-safe?
    this->handleRequest(message);
  }
  
}

// Retorna el codigo 
int ProtocolServer::analyzeMessage(std::string message) const {
  //0-host:port-figura-figura2...
  // Get the code of the message
  int code = atoi(&message[0]);
  //TODO: error message code.
  // TODO: get the IP from 
  if (!this->checkHost(message)) {
    return -1; // Can't send message back. Nothing is sent.
  }
  
  switch(code) {
    case LEGO_DISCOVER:
      return LEGO_DISCOVER;
      break;
    case LEGO_PRESENT:
      return LEGO_PRESENT;
      break;
    case LEGO_RELEASE:
      return LEGO_RELEASE;
      break;
    default: // message structure is ok, but code isn't valid. 
      return RESPOND_ERROR; // -2
  }
}

void ProtocolServer::respond(int code, std::string ip) const {
  // Calls the controller for it to respond.
  if (code == LEGO_PRESENT) {
    // controller.handle(code, ip, this->extract_figures(message));
  } else {
    // controller.handle(code, ip);
  }
}

void ProtocolServer::handleRequest(std::string message) const {
  // llama a analyze message
  // dependiendo de la respuesta llama a respond
  int code = this->analyzeMessage(message);
  if (code == -1) {
    return;
  }
  this->respond(code, this->getIP(message));
}


bool ProtocolServer::checkHost(std::string message) const {
  // First character doesn't matter anymore.
  bool st;
  st = (message[1] == SEPARATOR);
  // Get the IP address of the message
  struct sockaddr_in sa;
  std::string strIP = this->getIP(message);
  int validIP = inet_pton(AF_INET, strIP.c_str(), &(sa.sin_addr));
  return validIP && st;
}

// ! Assumes that the message has the right format.
std::string ProtocolServer::getIP(std::string message) const {
  // First character doesn't matter anymore.
  // TODO: check substring generation.
  return message.substr(2, message.find(":") - 1);
}

void ProtocolServer::start() {
  // Create 7 threads and call them to execute keepListening.
  for (int i{0}; i < THREAD_AMOUNT; i++) {
    // FIXME: ??
    this->workers.emplace_back(&ProtocolServer::keepListening, this);
  }
}

std::string ProtocolServer::extract_figures(std::string message) const {
  int index = findNthOccurrence(message, SEPARATOR, 2);
  if (index == -1) {
    return "";
  }
  return message.substr(index + 1);
}

void ProtocolServer::stop() {
  this->keepListeningFlag = false;
  for (auto &worker : workers) {
    worker.join();
  }
}

int findNthOccurrence(const std::string& str, char c, int n) {
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == c) {
            count++;
            if (count == n) {
                return i;
            }
        }
    }
    return -1;  // Character not found or nth occurrence not found
}

/**
void FigureHttpsServer::start() {
  listener.bind(PORT);

  listener.listen(QUEUE);

  for (int i{0}; i < NUM_WORKERS; ++i) {
    this->workers.emplace_back(&FigureHttpsServer::handleRequests, this);
  }

  Logger::info("Listener certificates: \n" + listener.getCerts());

  Logger::info("Listening.");

  while (true) {
    try {
      auto client{listener.accept()};
      Logger::info("Accepted connection with socket: " +
                   to_string(client->getSocketFD()));
      this->clientQueue.enqueue(client);
    } catch (exception &e) {
      Logger::error("Listener error: ", e);
    }
  }
}
*/

/*
void FigureHttpsServer::stop() {
  for (auto &worker : workers) {
    clientQueue.enqueue(nullptr);
  }

  for (auto &handler : workers) {
    handler.join();
  }
}

*/