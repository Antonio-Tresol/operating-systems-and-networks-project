// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Jean Paul Chacon Gonzalez <jean.chacongonzalez@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "../include/model/Figure.hpp"

using std::ostream;
using std::pair;
using std::regex;
using std::smatch;
using std::string;
using std::to_string;
using std::vector;

using Row = pair<string, int>;  // description, amount

Figure Figure::fromHtml(const string &html) {
  string::const_iterator searchStart(html.cbegin());
  string::const_iterator searchEnd(html.cend());

  smatch matchName;
  regex regName{"Nombre: ([A-Za-z]+)"};

  string name;
  if (regex_search(searchStart, searchEnd, matchName, regName)) {
    name = matchName[1];
  }

  smatch matchParts;
  regex regParts{
      "(?:brick|plate|flag|eyes|bracket|cone|slopes) "
      "(?:[0-9]x[0-9]|[0-9]x[0-9]-[0-9]x[0-9] )?(?:[a-z ]+)"};

  smatch matchAmount;
  regex regAmount{"[0-9]+(?=</TD>)"};

  vector<Row> inputParts;
  while (regex_search(searchStart, searchEnd, matchParts, regParts) &&
         regex_search(searchStart, searchEnd, matchAmount, regAmount)) {
    inputParts.emplace_back(matchParts[0], stoi(matchAmount[0]));
    searchStart = matchParts.suffix().first;
  }
  return {name, inputParts};
}

ostream &operator<<(ostream &os, const Figure &figure) {
  return os << std::string(figure);
}

Figure::operator std::string() const {
  string upperCaseName{name};
  transform(upperCaseName.begin(), upperCaseName.end(), upperCaseName.begin(),
            ::toupper);

  string asString{upperCaseName + "\n"};

  int totalParts{0};
  for (vector<Row>::size_type elem{0}; elem < parts.size(); elem++) {
    asString += to_string(parts[elem].second);
    asString += " pieces of ";
    asString += parts[elem].first;
    // 3 pieces of LEGO
    asString += "\n";
    totalParts += parts[elem].second;
  }
  asString = asString + "Total amount of parts for " + name +
             " is: " + to_string(totalParts);

  return asString;
}
