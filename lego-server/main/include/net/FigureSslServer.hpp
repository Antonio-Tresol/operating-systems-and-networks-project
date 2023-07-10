// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <memory>

#include "./net/SslServer.hpp"
#include "../controller/FigureSslController.hpp"

class FigureSslServer : SslServer {
public:
    using SslServer::SslServer;

    using SslServer::start;
private:
    static bool validateRequest(const std::string &request);

    void handleClient(const std::shared_ptr<IPv4SslSocket> &client) override;

    FigureSslController figureSslController{};
};