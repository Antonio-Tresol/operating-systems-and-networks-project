// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <memory>
#include <string>

#include "../controller/FigureSslController.hpp"
#include "./net/SslServer.hpp"

class FigureSslServer : public SslServer {
 public:
  FigureSslServer() = delete;

  FigureSslServer(int32_t numWorkers, const std::string& certPath, int32_t port,
                  FigureHtmlRepository& figureHtmlRepository);

  using SslServer::start;
  using SslServer::stop;

 private:
  static bool validateRequest(const std::string& request);

  void handleClient(const std::shared_ptr<IPv4SslSocket>& client) override;

  FigureSslController figureSslController;
};