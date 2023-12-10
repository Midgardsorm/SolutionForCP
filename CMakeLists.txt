cmake_minimum_required(VERSION 3.27)

set(CMAKE_CXX_STANDARD 17)

project(ArithParsEval CXX)

include_directories(
  inc
  src
  test
)

set(PROJECT_HEADERS
  inc/ast.hpp
  inc/evaluators.hpp
  inc/parsers.hpp
  inc/validators.hpp
  inc/logger.hpp
)

set(PROJECT_SOURCES
  src/ast.cpp
  src/evaluators.cpp
  src/parsers.cpp
  src/validators.cpp
  src/logger.cpp
)

set(TEST_HEADERS
  test/test.hpp
)

set(TEST_SOURCES
  test/test.cpp
)

add_executable(ArithParsEval main.cpp
  ${PROJECT_SOURCES}
  ${PROJECT_HEADERS}
)

add_executable(ArithParsEval_Test mainTest.cpp
  ${PROJECT_SOURCES}
  ${PROJECT_HEADERS}
  ${TEST_SOURCES}
  ${TEST_HEADERS}
)