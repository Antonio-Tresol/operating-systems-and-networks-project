// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#pragma once

#include <string>

#include "net/Socket.hpp"

class HttpClient {
public:
    std::string get(const std::string& url);
};