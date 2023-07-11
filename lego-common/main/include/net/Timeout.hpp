#pragma once

#include <stdexcept>

class Timeout : public std::runtime_error {
public:
    Timeout() : std::runtime_error("Operation timed out") {}
};