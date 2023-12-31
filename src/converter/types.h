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
#pragma once

#ifndef H_TYPES
#define H_TYPES

/* The recognized types of `b2rust`. This document is extremely similar with `../parser/recognized_types.h`, except it uses a class and inheritance.
 */

#include "../parser/recognized_types.h"
#include <boost/multiprecision/cpp_int.hpp>

#include <map>

using cpp_int = boost::multiprecision::cpp_int;

class bool_t;
class i8_t;
class i16_t;
class i32_t;
class i64_t;
class i128_t;
class u8_t;
class u16_t;
class u32_t;
class u64_t;
class u128_t;
class string_t;
class IntegerType;
class ErrorType;

class Exp;
class RustExpression;
class Context;

/* Virtual class. */
class RustType {
public:
  // We put them here so that it is more organized.
  static bool_t bool_o;
  static i8_t i8_o;
  static i16_t i16_o;
  static i32_t i32_o;
  static i64_t i64_o;
  static i128_t i128_o;
  static u8_t u8_o;
  static u16_t u16_o;
  static u32_t u32_o;
  static u64_t u64_o;
  static u128_t u128_o;
  static string_t string_o;
  static IntegerType integer_o;
  static ErrorType error_o;

  // The converting map.
  static std::map<std::string, const RustType*> types;

  static std::map<std::string, std::string> operationAssociation;

  virtual std::string PrintMe() const = 0;
  virtual std::string PrintMeDefault() const = 0;
  virtual void DebugMe(std::ostream&) const = 0;

  virtual std::string* debugMe() const;
  virtual const RustType* convertIfPartial(const Context*) const;
};

// usefull for namespace to load static types map
bool loadTypesFromConfig();

// List of all recognized types objects. NOTE that it should absolutely match the ones defind in `RightExprType`, or it will not recognize them!

//=========================================Atomic Type=================================================//

//************Signed integer *************//
class i8_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class i16_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class i32_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class i64_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class i128_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

//************Unsigned integer *************//
class u8_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class u16_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class u32_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class u64_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class u128_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

//*********others*************//
class bool_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class string_t : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class IntegerType : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

class ErrorType : public RustType {
  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const;
};

// Why "partial" tabular ?
// The size of partial tabular must be converted, but can not be converted during the checking
// So for this particular case, a partial tabular is created, it is not really a RustType but it can be converted into RustType
// with the method convertMeIfPartial
class PartialTabular : public RustType {
public:
  PartialTabular(const Exp* a, const RustType* t);

  // The number of elements
  const Exp* size;

  // The type there’s in.
  const RustType* elementsType;

  std::string PrintMe() const;
  std::string PrintMeDefault() const;

  const RustType* convertIfPartial(const Context*) const;
  void DebugMe(std::ostream&) const {};
};

class RustTabular : public RustType {
public:
  RustTabular(const RustExpression* a, const RustType* t);

  // The number of elements.
  const RustExpression* size;

  // The type there’s in.
  const RustType* elementsType;

  // The constructor.

  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const {};
};

// Translated B set, it has just the title of the enum, the content of the enum can be found in the context
class enumType : public RustType {
public:
  enumType(const std::string*);

  // The name of the enum.
  const std::string* const name;

  std::string PrintMe() const;
  std::string PrintMeDefault() const;
  void DebugMe(std::ostream&) const {};
};

#endif
