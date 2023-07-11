#pragma once

#include "./controller/ProtocolController.hpp"
#include "./net/ProtocolClient.hpp"
#include "./data/FigureHtmlRepository.hpp"

#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>

class FigureProtocolController : public ProtocolController {

public:
    FigureProtocolController() = delete;

    explicit FigureProtocolController(FigureHtmlRepository& figureHtmlRepository);

    ~FigureProtocolController();

    void handle(int code, std::string ip, std::string body) override;

    void presentBcast();

private:
    ProtocolClient protocolClient{INTERMEDIARY_UDP_PORT};

    FigureHtmlRepository& figureHtmlRepository;
};