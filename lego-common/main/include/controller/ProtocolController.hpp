// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>

#include "../net/ProtocolHeader.hpp"

class ProtocolController {
 public:
  virtual void handle(int code, std::string ip, std::string body) = 0;
};

// TODO: Implementar estos m[etodos en la subclase apropiada

/**
   * @brief When a LEGO_PRESENT message is received, this function extracts the
   * figures from the message.
   *
   * @param message Raw message from socket.
   * @return std::string Figures
   */
// std::string extractFigures(std::string message) const;

// std::string ProtocolServer::extractFigures(std::string message) const {
//    int index = findNthOccurrence(message, SEPARATOR, 2);
//    if (index == -1) {
//        return "";
//    }
//    return message.substr(index + 1);
//}