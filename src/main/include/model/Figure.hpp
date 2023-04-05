// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.

#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using Row = std::pair<std::string, int>; // description, amount

class Figure {
 public:
  static Figure fromHtml(const std::string &html);

  friend std::ostream& operator<<(std::ostream& os, const Figure& figure);

  Figure() = delete;

  const std::string name;
  const std::vector<Row> parts;

private:
    Figure(std::string name, const std::vector<Row>& parts) : name(std::move(name)), parts(parts) {}
};

Figure Figure::fromHtml(const std::string &html) {
    std::string name; // Fill with parsed HTML
    std::vector<Row> inputParts; // Fill with parsed HTML

    return {name, inputParts};
}

std::ostream& operator<<(std::ostream& os, const Figure& figure) {
    std::string asString = ""; // TODO
    int totalParts = 0;
    for (std::vector<Row>::size_type elem = 0; elem < figure.parts.size();
      elem++) {
        asString += std::to_string(figure.parts[elem].second);
        asString += " pieces of ";
        asString += figure.parts[elem].first;
        // 3 pieces of lego
        asString += "\n";
        totalParts += figure.parts[elem].second;
    }
    asString = asString + "Total amount of parts for" + figure.name + " is: "
      + std::to_string(totalParts); 
    return os << asString;
}
