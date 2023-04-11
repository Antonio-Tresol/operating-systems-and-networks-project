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
/**
 * @brief a class that represents a figure
 * @details contains the name, parts and amount of parts of a figure
 */
class Figure {
public:
    /**
     * @brief parses a string containing html and returns a Figure object
     * @details uses regex to find the name, parts and amount of parts in the html
     * @param html a string containing html
     * @return a Figure object
     */
    static Figure fromHtml(const std::string &html);
    /**
     * @brief overloads the << to interact with the Figure object and print it
     * @details prints the name, parts and amount of parts in the Figure object
     * @param os an ostream object
     * @param figure a Figure object
     * @return an ostream object
     */
    friend std::ostream &operator<<(std::ostream &os, const Figure &figure);

    Figure() = delete;

    const std::string name; // name of the figure
    const std::vector<Row> parts; // part description and amount

private:
    /**
     * @brief a constructor that creates a Figure object
     * @param name name of the figure
     * @param parts a vector of pairs in format (part, amount)
     */
    Figure(std::string name, const std::vector<Row> &parts)
            : name(std::move(name)), parts(parts) {}
};
