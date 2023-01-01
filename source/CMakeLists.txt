cmake_minimum_required(VERSION 3.0)
project(Uno++)

set(CMAKE_CXX_STANDARD 17)

add_executable(Uno++ main.cpp dataTypes.hpp cardFunctions.hpp gameFunctions.hpp)
