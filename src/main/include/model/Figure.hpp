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
using Reg = std::regex;
using Match = std::smatch;
using Row = std::pair<std::string, int>; // description, amount

class Figure {
 public:
  static Figure fromHtml(const std::string &html);

  friend std::ostream& operator<<(std::ostream& os, const Figure& figure);

  Figure() = delete;

  const std::string name;
  const std::vector<Row> parts;

private:
    Figure(std::string name, const std::vector<Row>& parts)
      : name(std::move(name)), parts(parts) {}
};

Figure Figure::fromHtml(const std::string &html) {
  std::string name;
  std::vector<Row> inputParts;
  Reg regName =
      Reg("/lego/(?:[a-zA-Z]+)/([a-zA-Z]+)(?=.jpg\" width=500 height=500)");
  Reg regParts("(?:brick|plate|flag) (?:[0-9]x[0-9] )?(?:[a-z ]+)");
  Reg regAmount("[0-9]+(?=</TD>)");
  Match matchName;
  Match matchParts;
  Match matchAmount;
  std::string::const_iterator searchStart(html.cbegin());
  std::string::const_iterator searchEnd(html.cend());
  if (std::regex_search(searchStart, searchEnd, matchName, regName)) {
    name = matchName[1];
  }
  while (std::regex_search(searchStart, searchEnd, matchParts, regParts)) {
    for (auto x : matchParts) {
      inputParts.push_back(Row(x, 0));
    }
    searchStart = matchParts.suffix().first;
  }
  searchStart = html.cbegin();
  searchEnd = html.cend();
  int i = 0;
  while (std::regex_search(searchStart, searchEnd, matchAmount, regAmount)) {
    for (auto x : matchAmount) {
      inputParts[i].second = std::stoi(x);
    }
    searchStart = matchAmount.suffix().first;
    i = i + 1;
  }
  return Figure(name, inputParts);
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
    asString = asString + "Total amount of parts for " + figure.name + " is: "
      + std::to_string(totalParts); 
    return os << asString;
}
