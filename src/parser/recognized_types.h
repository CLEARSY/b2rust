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
#ifndef H_RECOGNIZED_TYPES
#define H_RECOGNIZED_TYPES

#include "../error_codes.h"

#include <string>

typedef enum RecognizedType {
  rust_i128,
  rust_i64,
  rust_i32,
  rust_i16,
  rust_i8,
  rust_bool,
  rust_u128,
  rust_u64,
  rust_u32,
  rust_u16,
  rust_u8,
  STRING
} RecognizedType;


// Checks if the type can be recognized.
bool Recognizable(std::string);


// Convert string to enum. Has to be recognizable.
RecognizedType recognizedTypeFromString(const std::string&);

#endif
