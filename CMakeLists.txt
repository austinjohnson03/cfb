cmake_minimum_required(VERSION 3.14)
project(cfb VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(CLI11 CONFIG REQUIRED)
find_package(cpr CONFIG REQUIRED)

add_executable(cfb
  src/main.cpp
)

target_link_libraries(cfb 
  PRIVATE
    CLI11::CLI11
    cpr::cpr
)
