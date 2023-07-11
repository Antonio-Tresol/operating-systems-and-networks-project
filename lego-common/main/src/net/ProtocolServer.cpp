// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../../include/net/ProtocolServer.hpp"

#include <arpa/inet.h>

#include "logging/Logger.hpp"

#define RESPOND_ERROR -2
#define THREAD_AMOUNT 7

ProtocolServer::ProtocolServer(int port, ProtocolController &protocolController)
    : receiverSocket(port),
      protocolController(protocolController),
      keepListeningFlag(true) {
  receiverSocket.bind();
}

ProtocolServer::~ProtocolServer() { stop(); }

void ProtocolServer::keepListening(int worker_pos) const {
  // Loop for listening (receiving)
  while (keepListeningFlag) {
    //        POSIX defines send/recv as atomic operations, so assuming you're
    //        talking about POSIX send/recv then yes, you can call them
    //        simultaneously from multiple threads and things will work.
    //
    //        This doesn't necessarily mean that they'll be executed in parallel
    //        -- in the case of multiple sends, the second will likely block
    //        until the first completes. You probably won't notice this much, as
    //        a send completes once its put its data into the socket buffer.
    //
    //        If you're using SOCK_STREAM sockets, trying to do things a
    //        parallel is less likely to be useful as send/recv might send or
    //        receive only part of a message, which means things could get split
    //        up.
    //
    //        Blocking send/recv on SOCK_STREAM sockets only block until they
    //        send or recv at least 1 byte, so the difference between blocking
    //        and non-blocking is not useful.
    //        https://stackoverflow.com/questions/1981372/are-parallel-calls-to-send-recv-on-the-same-socket-valid
    std::string message = this->receiverSocket.receive();
    Logger::info("ProtocolServer: Received message on worker " +
                 std::to_string(worker_pos));
    this->handleRequest(message, worker_pos);
  }
}

// Returns the message code.
int ProtocolServer::validateMessage(std::string message) const {
  // - being the separator
  // 0-host:port-figura-figura2...
  if (message.size() < 2) {
    return -1;
  }

  // Get the code of the message
  int code = atoi(&message[0]);

  if (!this->checkHost(message)) {
    return -1;  // Can't send message back. Nothing is sent.
  }

  switch (code) {
    case LEGO_DISCOVER:
      return LEGO_DISCOVER;
    case LEGO_PRESENT:
      return LEGO_PRESENT;
    case LEGO_RELEASE:
      return LEGO_RELEASE;
    default:                 // message structure is ok, but code isn't valid.
      return RESPOND_ERROR;  // -2
  }
}

void ProtocolServer::handleRequest(std::string message, int worker_pos) const {
  // Calls analyzeMessage and depending on the response calls respond.
  int code = this->validateMessage(message);
  if (code == -1) {
    Logger::info("ProtocolServer: Invalid message on worker " +
                 std::to_string(worker_pos));
    return;
  }

  std::string messageType{getLegoMessageCodeName(code)};

  Logger::info("ProtocolServer: Handling " + messageType + " on worker " +
               std::to_string(worker_pos));

  protocolController.handle(code, getIP(message), message);
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
  std::string::size_type pos = message.find(":");
  if (pos != std::string::npos) {
    message = message.substr(0, pos);
  }
  return message.substr(2);
}

void ProtocolServer::start() {
  // Create 7 threads and call them to execute keepListening.
  for (int i{0}; i < THREAD_AMOUNT; i++) {
    this->workers.emplace_back(&ProtocolServer::keepListening, this, i);
  }
  Logger::info("ProtocolServer: Listening");
}

void ProtocolServer::stop() {
  this->keepListeningFlag = false;
  for (auto &worker : workers) {
    worker.join();
  }
  Logger::info("ProtocolServer: Stopped");
}
