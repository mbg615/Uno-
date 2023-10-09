cmake_minimum_required(VERSION 3.0)
project(Uno++)

set(CMAKE_CXX_STANDARD 17)

# PROVIDE CUSTOM PATH FOR BOOST
set(Boost_NO_SYSTEM_PATHS TRUE)
if (Boost_NO_SYSTEM_PATHS)
    set(BOOST_ROOT "/opt/homebrew/Cellar/boost/1.82.0_1")
    set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
    set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS)
find_package(Boost REQUIRED regex date_time system filesystem thread graph program_options)
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(Uno++ main.cpp dataTypes.hpp Card.hpp Card.cpp Player.hpp Player.cpp cardFunctions.hpp gameFunctions.hpp iterable_stack.hpp)