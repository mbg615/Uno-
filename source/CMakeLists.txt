cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(Uno++)

# PROVIDE CUSTOM PATH FOR BOOST
set(Boost_NO_SYSTEM_PATHS TRUE)
if(Boost_NO_SYSTEM_PATHS)
        set(BOOST_ROOT "/opt/homebrew/Cellar/boost/1.83.0")
        set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
        set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
endif (Boost_NO_SYSTEM_PATHS)

find_package(Boost REQUIRED regex date_time filesystem thread graph program_options)
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(Uno++ Card/Card.hpp Card/Card.cpp Player/Player.hpp Player/Player.cpp Card/cardFunctions.hpp Game/gameFunctions.hpp Game/dataTypes.hpp Game/iterable_stack.hpp main.cpp)