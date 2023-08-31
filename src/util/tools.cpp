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
#include "tools.h"

std::string Tools::expandTilde(const std::string& path) {
  std::string expandedPath = path;

  if (!expandedPath.empty() && expandedPath[0] == '~') {
    const char* homePath = std::getenv("HOME");
    if (homePath != nullptr) {
      expandedPath.replace(0, 1, homePath);
    }
  }

  return expandedPath;
}


std::string Tools::getLastWord(std::string op_name) {
  size_t dotIndex = op_name.find_last_of(".");
  // if the op was not renamed
  if (dotIndex == std::string::npos) {
    return op_name;
  } else {
    // return word after dot
    return op_name.substr(dotIndex + 1);
  }
}



std::string Tools::getFirstWord(std::string op_name) {
  size_t dotIndex = op_name.find_first_of(".");
  // if the op was not renamed
  if (dotIndex == std::string::npos) {
    return op_name;
  } else {
    // return word before dot
    return op_name.substr(0, dotIndex);
  }
}