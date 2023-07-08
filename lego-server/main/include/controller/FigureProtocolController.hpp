#pragma once

#include "../../../../lego-common/main/include/controller/ProtocolController.hpp"
#include "../../../../lego-common/main/src/net/ProtocolClient.cpp"

#include <vector>
#include <string>
#include <unordered_map>

class FigureProtocolController : public ProtocolController {

public:
  FigureProtocolController(int port);
  ~FigureProtocolController();

  void handle(int code, std::string ip, std::string body);
  
private:
  std::vector<std::string> findAllHtmlFiles();

  std::vector<std::string> availableFigures; 
  ProtocolClient protocolClient;

};