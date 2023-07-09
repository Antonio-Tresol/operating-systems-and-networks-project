// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <string>

#include "./net/ProtocolHeader.hpp"

class ProtocolController {
public:
    virtual void handle(int code, std::string ip, std::string body) = 0;
};


// TODO: Implementar estos m[etodos en la subclase apropiada
//std::string ProtocolServer::extractFigures(std::string message) const {
//    int index = findNthOccurrence(message, SEPARATOR, 2);
//    if (index == -1) {
//        return "";
//    }
//    return message.substr(index + 1);
//}

//int ProtocolServer::findNthOccurrence(const std::string& str, char c, int n) const {
//    int count = 0;
//    for (int i = 0; i < str.length(); i++) {
//        if (str[i] == c) {
//            count++;
//            if (count == n) {
//                return i;
//            }
//        }
//    }
//    return -1;  // Character not found or nth occurrence not found
//}