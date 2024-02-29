# TODO try to lower the requirement
cmake_minimum_required(VERSION 3.22)
project(b2rust)
# -------------------------
# Parameters
# -------------------------
# If you want a debug version.
add_compile_options("-g")


set(CMAKE_CXX_STANDARD 17)  # Spécifie la version C++17

# The directory containing the sources.
set(SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/)
# The source files. `GLOB` is often used, but its use is discouraged from the developpers.
set(SOURCE_FILES
  ${SRC}/b2rust.cpp

  ${SRC}/util/tools.cpp

  ${SRC}/parser/parser.cpp
  ${SRC}/parser/tinyxml2ext.cpp
  ${SRC}/parser/expression_leaf.cpp
  ${SRC}/parser/recognized_types.cpp
  ${SRC}/parser/miscellaneous.cpp

  ${SRC}/parser/bxml/abstraction.cpp
  ${SRC}/parser/bxml/assertion.cpp
  ${SRC}/parser/bxml/assignementsub.cpp
  ${SRC}/parser/bxml/binaryexp.cpp
  ${SRC}/parser/bxml/binarypred.cpp
  ${SRC}/parser/bxml/binarypredop.cpp
  ${SRC}/parser/bxml/booleanliteral.cpp
  ${SRC}/parser/bxml/booleanexp.cpp
  ${SRC}/parser/bxml/case_sub.cpp
  ${SRC}/parser/bxml/emptyset.cpp
  ${SRC}/parser/bxml/enumeratedvalues.cpp
  ${SRC}/parser/bxml/exp.cpp
  ${SRC}/parser/bxml/expcomparison.cpp
  ${SRC}/parser/bxml/expressiontype.cpp
  ${SRC}/parser/bxml/id.cpp
  ${SRC}/parser/bxml/ifsub.cpp
  ${SRC}/parser/bxml/initialisation.cpp
  ${SRC}/parser/bxml/instancelisttype.cpp
  ${SRC}/parser/bxml/instruction.cpp
  ${SRC}/parser/bxml/integerliteral.cpp
  ${SRC}/parser/bxml/invariant.cpp
  ${SRC}/parser/bxml/machine.cpp
  ${SRC}/parser/bxml/operation.cpp
  ${SRC}/parser/bxml/operations.cpp
  ${SRC}/parser/bxml/operationcall.cpp
  ${SRC}/parser/bxml/naryexp.cpp
  ${SRC}/parser/bxml/narysub.cpp
  ${SRC}/parser/bxml/narypred.cpp
  ${SRC}/parser/bxml/parameters.cpp
  ${SRC}/parser/bxml/parametersdeclaration.cpp
  ${SRC}/parser/bxml/predgroup.cpp
  ${SRC}/parser/bxml/predicatetype.cpp
  ${SRC}/parser/bxml/promotes.cpp
  ${SRC}/parser/bxml/promotedoperationtype.cpp
  ${SRC}/parser/bxml/referencedmachine.cpp
  ${SRC}/parser/bxml/sees.cpp
  ${SRC}/parser/bxml/select.cpp
  ${SRC}/parser/bxml/set.cpp
  ${SRC}/parser/bxml/sets.cpp
  ${SRC}/parser/bxml/skip.cpp
  ${SRC}/parser/bxml/stringliteral.cpp
  ${SRC}/parser/bxml/substitutiontype.cpp
  ${SRC}/parser/bxml/type.cpp
  ${SRC}/parser/bxml/typeinfos.cpp
  ${SRC}/parser/bxml/type_infos_type.cpp
  ${SRC}/parser/bxml/unarypred.cpp
  ${SRC}/parser/bxml/valuation.cpp
  ${SRC}/parser/bxml/variablestype.cpp
  ${SRC}/parser/bxml/varin.cpp
  ${SRC}/parser/bxml/while.cpp

  ${SRC}/checker/checker.cpp

  ${SRC}/converter/arrayaccess.cpp
  ${SRC}/converter/block.cpp
  ${SRC}/converter/declaration.cpp
  ${SRC}/converter/delegatecall.cpp
  ${SRC}/converter/function.cpp
  ${SRC}/converter/functioncall.cpp
  ${SRC}/converter/match.cpp
  ${SRC}/converter/miscellaneous.cpp
  ${SRC}/converter/r_assignement.cpp
  ${SRC}/converter/r_case.cpp
  ${SRC}/converter/r_enum.cpp
  ${SRC}/converter/r_expression.cpp
  ${SRC}/converter/r_if.cpp
  ${SRC}/converter/r_instruction.cpp
  ${SRC}/converter/r_module.cpp
  ${SRC}/converter/r_while.cpp
  ${SRC}/converter/types.cpp



  ${SRC}/converter/r_predicate/r_predicate.cpp


  ${SRC}/printer/printer.cpp
  ${SRC}/printer/component_printers.cpp

  ${SRC}/input.cpp
  ${SRC}/debug.cpp
)
# The directory containing the binaries.
set(BIN ${CMAKE_CURRENT_SOURCE_DIR}/bin)
# The test directory.
set(TESTS ${CMAKE_CURRENT_SOURCE_DIR}/tests)
# The script generating the tests.
set(GEN_TESTS_SCRIPT ${TESTS}/gen_tests.sh)
# The tests file.
set(TESTS_FILE ${TESTS}/tests_file.cmake)
# The `comparison` directory.
set(COMPARISON_DIR ${TESTS}/comparison/)
# The `errors` directory.
set(ERRORS_DIR ${TESTS}/errors/)
# The `main` directory.
set(MAIN_DIR ${TESTS}/main/)
# The base_module directory
set(BASE_DIR ${TESTS}/base_module/)
# The c4b bank test directory
set(C4B_DIR ${TESTS}/c4b/)
# The industrial test directory
set(INDUSTRIAL_DIR ${TESTS}/Industrial/)
# The `call_code` directory.
set(CALL_CODE_DIR ${TESTS}/call_code/)


# -------------------------------------------

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN})
add_executable(b2rust ${SOURCE_FILES})

find_library(TINYXML2_LIBRARY
	NAMES tinyxml2
	PATHS /usr/lib/x86_64-linux-gnu)
target_link_libraries(b2rust ${TINYXML2_LIBRARIES} -ltinyxml2)

find_package(Boost REQUIRED)
target_link_libraries(b2rust ${Boost_LIBRARIES})

# Add warning flags
if(MSVC)
  target_compile_options(b2rust PRIVATE /W4 /WX)
else()
  target_compile_options(b2rust PRIVATE -Wall -Wextra -Wpedantic)
endif()

# The tests.
execute_process(COMMAND ${GEN_TESTS_SCRIPT} ${BIN}/b2rust ${TESTS_FILE} ${COMPARISON_DIR} ${ERRORS_DIR} ${MAIN_DIR} ${CALL_CODE_DIR} ${BASE_DIR} ${C4B_DIR} ${INDUSTRIAL_DIR})

enable_testing()

# The tests list.
include(${TESTS_FILE})
