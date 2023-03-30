// Copyright 2023 Ariel Arevalo Alvarado <ariel.arevalo@ucr.ac.cr>.
// Copyright 2023 Antonio Badilla Olivas <anthonny.badilla@ucr.ac.cr>.
// Copyright 2023 Geancarlo Rivera Hernandez
// <geancarlo.riverahernandez@ucr.ac.cr>.

#include "FigureRepository.hpp"

Figure FigureRepository::findByName(std::string name) {
  // request direction page url
  std::string request = FIGURE_URL + name + "\r\n";
  // response = html
  std::string response = "";

  // create a socket
  Socket socket('s', false);

  // buffer to store the html characters
  char buff[SIZE];

  // initialize buffer
  memset(buff, 0, SIZE);
  // counter to store the number of characters read
  int count = 0;

  // initialize ssl
  //! socket.InitSSL();

  // connect to the server with https service
  //! socket.SSLConnect((char*) HOST, (char*) "https");

  // send the request
  //! socket.SSLWrite((void*) request.c_str(), request.length());

  /*
  // read the Htlm characters and store them in the response string
  // while there are characters to read
  while ((count = socket.SSLRead(buff, SIZE)) > 0) {
    // append the characters to the response string
    response.append(buff, SIZE);
    // clear the buffer
    memset(buff, 0, SIZE);
  }
  */

  // create a figure with the html response
  Figure figure(response);

  // return the figure
  return figure;
}
