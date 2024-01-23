cmake_minimum_required(VERSION 3.12)


project(Midas VERSION 0.0.1)

set(SOURCES
src/midas/scanner/scanner.cpp
test/main.cpp)

set(HEADERS

include/midas/scanner/scanner.hpp
include/midas/token/token.hpp
)

include_directories(include)

add_executable(Midas ${SOURCES} ${HEADERS})

