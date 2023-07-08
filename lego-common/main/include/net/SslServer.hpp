//
// Created by ariel on 6/24/23.
//
#ifndef PI_REDES_SISTEMAS_OPERATIVOS_SSLSERVER_HPP
#define PI_REDES_SISTEMAS_OPERATIVOS_SSLSERVER_HPP

#include <map>
#include <memory>
#include <thread>
#include <vector>

using Worker = std::thread;

#include "../concurrency/Queue.hpp"
#include "socket/IPv4SslSocket.hpp"
class SslServer {
 public:
  SslServer(int32_t numWorkers, const std::string& certPath,
                     int32_t port);

  virtual ~SslServer();

  [[noreturn]] void start();
  void stop();

 protected:
  const std::string CERT_PATH;
  const int32_t NUM_WORKERS;
  const int32_t PORT;
  static constexpr int QUEUE{128};

  IPv4SslSocket listener;
  Queue<std::shared_ptr<IPv4SslSocket>> clientQueue{};
  std::vector<Worker> workers{};

  virtual void handleClient(const std::shared_ptr<IPv4SslSocket>& client) = 0;

 private:
  void handleRequests();
  virtual void handleAcceptError(const std::exception& e) = 0;
};

#endif  // PI_REDES_SISTEMAS_OPERATIVOS_SSLSERVER_HPP
