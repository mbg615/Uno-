cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(Uno++)

add_executable(Uno++ Card/Card.hpp Card/Card.cpp Player/Player.hpp Player/Player.cpp Card/cardFunctions.hpp Game/gameFunctions.hpp Game/dataTypes.hpp Game/iterable_stack.hpp main.cpp)