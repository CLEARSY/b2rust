/*
   This file is part of b2rust.
   Copyright © CLEARSY 2023
   b2rust is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef H_PRINTER
#define H_PRINTER

#include <string>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/wait.h>


#include "../b2rust.h"
#include "../input.h"
#include "../error_codes.h"
#include "../converter/r_module.h"


// Handles a single output file.
class Printer {
public:
  // You need to put the exact path, e.g. `/home/atelierb/code/component.rs`.
  Printer(const std::string* path, bool* error);
  ~Printer();

  void print(const std::string*);

private:
  const std::string path;

  std::ofstream codeStream;
  
  friend std::ostream& operator<<(std::ostream& os, const Printer*);
};


void PrintAll(const std::string*, const RustModule*);

#endif
