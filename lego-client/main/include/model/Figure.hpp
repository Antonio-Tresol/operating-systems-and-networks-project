// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez <geancarlo.riverahernandez@ucr.ac.cr>.

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <regex>

using Row = std::pair<std::string, int>; // description, amount

/**
 * @brief A LEGO figure.
 * @details Contains the name, parts and amount of parts for a figure.
 */
class Figure {
public:
    /**
     * @brief Parses a string containing HTML for the name and parts of a Figure.l
     * @param html A string containing HTML for a Figure.
     * @return The resulting Figure.
     */
    static Figure fromHtml(const std::string &html);

    friend std::ostream &operator<<(std::ostream &os, const Figure &figure);

    explicit operator std::string() const;

    const std::string name;
    const std::vector<Row> parts;

private:
    Figure(std::string name, const std::vector<Row> &parts)
            : name(std::move(name)), parts(parts) {}
};
