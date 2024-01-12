cmake_minimum_required(VERSION 3.1)
project(B2RUST)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
  b2rust.cpp

  util/report.cpp
  util/tools.cpp

  parser/parser.cpp
  parser/miscellaneous.cpp

  parser/bxml/abstraction.cpp
  parser/bxml/assertion.cpp
  parser/bxml/assignementsub.cpp
  parser/bxml/binaryexp.cpp
  parser/bxml/binarypred.cpp
  parser/bxml/binarypredop.cpp
  parser/bxml/booleanliteral.cpp
  parser/bxml/booleanexp.cpp
  parser/bxml/case_sub.cpp
  parser/bxml/emptyset.cpp
  parser/bxml/enumeratedvalues.cpp
  parser/bxml/exp.cpp
  parser/bxml/expcomparison.cpp
  parser/bxml/expressiontype.cpp
  parser/bxml/id.cpp
  parser/bxml/ifsub.cpp
  parser/bxml/initialisation.cpp
  parser/bxml/instancelisttype.cpp
  parser/bxml/instruction.cpp
  parser/bxml/integerliteral.cpp
  parser/bxml/invariant.cpp
  parser/bxml/machine.cpp
  parser/bxml/operation.cpp
  parser/bxml/operations.cpp
  parser/bxml/operationcall.cpp
  parser/bxml/naryexp.cpp
  parser/bxml/narysub.cpp
  parser/bxml/narypred.cpp
  parser/bxml/parameters.cpp
  parser/bxml/parametersdeclaration.cpp
  parser/bxml/predgroup.cpp
  parser/bxml/predicatetype.cpp
  parser/bxml/promotes.cpp
  parser/bxml/promotedoperationtype.cpp
  parser/bxml/referencedmachine.cpp
  parser/bxml/sees.cpp
  parser/bxml/select.cpp
  parser/bxml/set.cpp
  parser/bxml/sets.cpp
  parser/bxml/skip.cpp
  parser/bxml/stringliteral.cpp
  parser/bxml/substitutiontype.cpp
  parser/bxml/type.cpp
  parser/bxml/typeinfos.cpp
  parser/bxml/type_infos_type.cpp
  parser/bxml/unarypred.cpp
  parser/bxml/valuation.cpp
  parser/bxml/variablestype.cpp
  parser/bxml/varin.cpp
  parser/bxml/while.cpp

  checker/checker.cpp

  converter/arrayaccess.cpp
  converter/block.cpp
  converter/declaration.cpp
  converter/delegatecall.cpp
  converter/function.cpp
  converter/functioncall.cpp
  converter/match.cpp
  converter/miscellaneous.cpp
  converter/r_assignement.cpp
  converter/r_case.cpp
  converter/r_enum.cpp
  converter/r_expression.cpp
  converter/r_if.cpp
  converter/r_instruction.cpp
  converter/r_module.cpp
  converter/r_while.cpp
  converter/types.cpp



  converter/r_predicate/r_predicate.cpp


  printer/printer.cpp
  printer/component_printers.cpp
  printer/instances_printer.cpp

  input.cpp
  debug.cpp
)

set(HEADERS
  converter/types.h
  converter/match.h
  converter/arrayaccess.h
  converter/declaration.h
  converter/function.h
  converter/r_instruction.h
  converter/miscellaneous.h
  converter/r_assignement.h
  converter/r_while.h
  converter/r_case.h
  converter/r_module.h
  converter/r_if.h
  converter/functioncall.h
  converter/delegatecall.h
  converter/r_expression.h
  converter/block.h
  converter/r_predicate/r_predicate.h
  b2rust.h
  input.h
  debug.h
  parser/parser.h
  parser/miscellaneous.h
  parser/bxml/stringliteral.h
  parser/bxml/unarypred.h
  parser/bxml/ifsub.h
  parser/bxml/narysub.h
  parser/bxml/case_sub.h
  parser/bxml/skip.h
  parser/bxml/expressiontype.h
  parser/bxml/binarypred.h
  parser/bxml/promotedoperationtype.h
  parser/bxml/promotes.h
  parser/bxml/initialisation.h
  parser/bxml/narypred.h
  parser/bxml/integerliteral.h
  parser/bxml/assertion.h
  parser/bxml/sub.h
  parser/bxml/sees.h
  parser/bxml/set.h
  parser/bxml/expcomparison.h
  parser/bxml/variablestype.h
  parser/bxml/select.h
  parser/bxml/predgroup.h
  parser/bxml/varin.h
  parser/bxml/booleanexp.h
  parser/bxml/typeinfos.h
  parser/bxml/booleanliteral.h
  parser/bxml/id.h
  parser/bxml/invariant.h
  parser/bxml/machine.h
  parser/bxml/emptyset.h
  parser/bxml/type_infos_type.h
  parser/bxml/instancelisttype.h
  parser/bxml/exp.h
  parser/bxml/operationcall.h
  parser/bxml/sets.h
  parser/bxml/abstraction.h
  parser/bxml/referencedmachine.h
  parser/bxml/type.h
  parser/bxml/naryexp.h
  parser/bxml/binarypredop.h
  parser/bxml/instruction.h
  parser/bxml/operation.h
  parser/bxml/operations.h
  parser/bxml/while.h
  parser/bxml/enumeratedvalues.h
  parser/bxml/parameters.h
  parser/bxml/parametersdeclaration.h
  parser/bxml/valuation.h
  parser/bxml/substitutiontype.h
  parser/bxml/binaryexp.h
  parser/bxml/assignementsub.h
  parser/bxml/predicatetype.h
  parser/expression_leaf.h
  parser/recognized_types.h
  error_codes.h

  printer/printer.h
  printer/instances_printer.h

  util/report.h
  util/tools.h
  checker/checker.h
)
# -------------------------------------------

add_executable(b2rust ${SOURCES} ${HEADERS})

include_directories(
  ${TINYXML2_INCLUDE_DIR}
  ${FMT_CXX_SOURCE_DIR}/include/
  )

find_package(Boost REQUIRED)

target_link_libraries(b2rust
  PRIVATE fmt::fmt-header-only
  -Bdynamic tinyxml2::tinyxml2 ${Boost_LIBRARIES})
