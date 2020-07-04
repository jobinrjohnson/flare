//
// Created by Jobin Johnson on 31/05/20.
//

#ifndef FLARE_DRIVER_H
#define FLARE_DRIVER_H

#include <fstream>
#include <iostream>
#include <string>

namespace lang {

class Parser;
class Scanner;
class location;

class Driver {

public:
  Driver();
  ~Driver();
  int parseFile(std::string &path);

private:
  Scanner *scanner;
  Parser *parser;
  location *cursor;

  int error_;

  friend class Parser;
  friend class Scanner;
};

} // namespace lang

#endif // FLARE_DRIVER_H
