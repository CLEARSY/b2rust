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
#ifndef H_R_EXPRESSION
#define H_R_EXPRESSION

#include "../error_codes.h"
#include "./miscellaneous.h"
#include "./types.h"
#include <climits>
#include <optional>
#include <stdlib.h>
#include <string>
#include <vector>

class RustType;

/* Pure virtual class, because an expression needs to have a type! */
class RustExpression {
  template <typename T> friend std::string* printIt(T*);

public:

  //Print the expression
  virtual std::string PrintMe() const = 0;

  //Print the default value of the expression according to its type
  virtual std::string PrintMeDefault() const;
  
  // Print me with explicit conversion, works only in binary expression
  virtual std::string PrintMeConst() const;

  //Cast explicitly an expression target to the type of this expression
  virtual std::string castToType(const RustExpression*) const;
  virtual std::string asConversion() const;
  
  virtual const RustType* getType() const = 0 ;


  virtual void DebugMe(std::ostream&) const = 0;
  friend std::ostream& operator<<(std::ostream& os, const RustExpression*);

private:
  std::string* debugMe() const;
};

// The different expressions.

/// @brief Represents an integer literal
class Int : public RustExpression {
public:
  const mathint_t value;

  const RustType* getType() const;

  operator std::string() const {
    return value;
  }
  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;

  Int(const std::string&);
  Int(size_t);
};

class Bool : public RustExpression {
public:
  const bool value;

  // METHODS.
  // std::string PrintType() const;
  const RustType* getType() const;
  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;

  Bool(const std::string&);
  Bool(bool);
};

class RustString : public RustExpression {
public:
  const std::string value;
  const RustType* getType() const;
  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;

  RustString(const std::string);
};

// A variable, global or local.
class Variable : public RustExpression {
public:
  const std::string name;
  const RustType* type;
  virtual const RustType* getType() const = 0;

  Variable(const std::string*, const RustType*);
};

/**
 * The function searches for the value in different scopes 
 *
 * @param context A pointer to the Context object containing the variable definitions.
 * @param value A pointer to the string containing the name of the variable to be resolved.
 * @return A pointer to a constant Variable object representing the resolved variable.
 *         If the variable is found, an appropriate subtype of Variable is returned based on its scope and type.
 *         If the variable is not found, an UnknownVariable is returned with a warning message.
 */
const Variable* _Variable(const Context*, const std::string*);

class GlobalVariable : public Variable {
public:
  std::string PrintMe() const;
  std::string PrintMeInit() const;
  void DebugMe(std::ostream&) const;

  const RustType* getType() const;
  GlobalVariable(const std::string*, const RustType*);
};

class GlobalConstant : public Variable {
public:
  const std::string structName;

  std::string PrintMe() const;
  std::string PrintMeInit() const;
  void DebugMe(std::ostream&) const;

  const RustType* getType() const;
  GlobalConstant(const std::string*, const RustType*);
};

class LocalVariable : public Variable {
public:
  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
  const RustType* getType() const;
  LocalVariable(const std::string*, const RustType*);
};

class UnknownVariable : public Variable {
public:
  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
  const RustType* getType() const;
  UnknownVariable(const std::string*, const RustType*);
};

class ParameterVariable : public Variable {
public:
  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
  const RustType* getType() const;
  ParameterVariable(const std::string*, const RustType*);
};

class FieldAccess : public Variable {
public:
  std::vector<std::string>* _path;
  std::string PrintMe() const;
  std::string PrintMeInit() const;
  void DebugMe(std::ostream&) const;
  const RustType* getType() const;
  FieldAccess(const std::string*, std::vector<std::string>*, const RustType*);
};

class ConstantAccess : public Variable {
public:
  const std::string* _path;
  std::string PrintMe() const;
  std::string PrintMeInit() const;
  void DebugMe(std::ostream&) const;
  const RustType* getType() const;
  ConstantAccess(const std::string*, const std::string*, const RustType*);
};

// An enumerator is considered as a "Variable". It could be corrected (maybe by changing the names?).
class Enumerator : public Variable {
public:
  // The `enum` it is defined in.
  std::string _enum;

  std::string PrintMe() const;
  void DebugMe(std::ostream&) const {};
  const RustType* getType() const;
  Enumerator(const std::string*, const std::string*, const RustType*);
};

typedef enum binaryExpression {
  addition,
  substraction,
  division,
  multiplication,
  left_shift,
  right_shift,
  bitwise_or,
  bitwise_xor,
  bitwise_and,
  exponentiation,
  modulo,
  tabularPosition,
  parameterPosition,
  interval,
  tuplePosition
} binaryExpression;

class BinaryRustExpression : public RustExpression {
public:
  binaryExpression type;
  const RustExpression* left_expr;
  const RustExpression* right_expr;

  const RustType* resultType;
  std::string castToType(const RustExpression*) const;
  std::string asConversion() const;

  std::string PrintMe() const;
  std::string PrintMeConst() const;
  void DebugMe(std::ostream&) const;
  const RustType* getType() const;
  BinaryRustExpression(const RustExpression*, const std::string*, const RustExpression*, const RustType*);
  BinaryRustExpression(const RustExpression*, const std::string*, const RustExpression*);
};

// Just a container for a vector.
class RustArray : public RustExpression {
public:
  // Caution, it might be void.
  std::vector<const RustExpression*> values;

  std::string PrintMe() const;
  void DebugMe(std::ostream&) const;
  const RustType* getType() const;

  std::string castToType(const RustExpression*) const;
  std::string asConversion() const;
};

// initialise array when using cartesian product
class RustUniformArray : public RustExpression {
public:
  const RustExpression* size;
  const RustExpression* value;

  std::string PrintMe() const;
  std::string castToType(const RustExpression*) const;
  std::string asConversion() const;

  void DebugMe(std::ostream&) const;
  const RustType* getType() const;
  RustUniformArray(const RustExpression*, const RustExpression*);
};

#endif
