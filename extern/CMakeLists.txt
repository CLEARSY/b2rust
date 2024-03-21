cmake_minimum_required(VERSION 3.11 FATAL_ERROR)

message(STATUS "fetching external dependencies")
include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG e69e5f977d458f2650bb346dadf2ad30c5320281
)

FetchContent_Declare(
  tinyxml2
  GIT_REPOSITORY https://github.com/leethomason/tinyxml2
  GIT_TAG 1dee28e51f9175a31955b9791c74c430fe13dc82
  )

FetchContent_MakeAvailable(fmt tinyxml2)
