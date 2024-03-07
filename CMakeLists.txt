# TODO try to lower the requirement
cmake_minimum_required(VERSION 3.22)


project(PROJECT_B2RUST)

set(CMAKE_CXX_STANDARD 17)  # Spécifie la version C++17

# The project name. The binary will be `${BIN}/${NAME}`.
set(NAME b2rust)

if (${CMAKE_PROJECT_NAME} STREQUAL ${PROJECT_NAME})
  set(PROJECT_IS_TOP_LEVEL TRUE)
else()
  set(PROJECT_IS_TOP_LEVEL FALSE)
endif()

if (PROJECT_IS_TOP_LEVEL)
	
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
add_subdirectory(extern)

# The tests.
execute_process(COMMAND ${GEN_TESTS_SCRIPT} ${BIN}/${NAME} ${TESTS_FILE} ${COMPARISON_DIR} ${ERRORS_DIR} ${MAIN_DIR} ${CALL_CODE_DIR} ${BASE_DIR} ${C4B_DIR} ${INDUSTRIAL_DIR})

enable_testing()

# The tests list.
include(${TESTS_FILE})

endif()

add_subdirectory(src)
