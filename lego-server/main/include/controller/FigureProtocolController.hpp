#pragma once

#include "../../../../lego-common/main/include/controller/ProtocolController.hpp"
#include "../../../../lego-common/main/src/net/ProtocolClient.cpp"
#include "data/FigureHtmlRepository.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

class FigureProtocolController : public ProtocolController {

public:
    FigureProtocolController() = delete;

    explicit FigureProtocolController(FigureHtmlRepository& figureHtmlRepository);

    void handle(int code, std::string ip, std::string body) override;

    void presentBcast();

private:
    std::filesystem::path getResourcePath();

    ProtocolClient protocolClient{INTERMEDIARY_UDP_PORT};

    FigureHtmlRepository& figureHtmlRepository;
};