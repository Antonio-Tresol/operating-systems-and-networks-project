// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>
#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <regex>

using Row = std::pair<std::string, int>; // description, amount

class Figure {
public:
    static Figure fromHtml(const std::string &html);

    friend std::ostream &operator<<(std::ostream &os, const Figure &figure);

    Figure() = delete;

    const std::string name;
    const std::vector<Row> parts;

private:
    Figure(std::string name, const std::vector<Row> &parts)
            : name(std::move(name)), parts(parts) {}
};
