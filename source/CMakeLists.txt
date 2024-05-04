cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 17)

project(Uno++)

# Try and find Boost
find_package(Boost REQUIRED)

if(Boost_FOUND)
        # Boost found using BOOST_INCLUDE_DIRS and Boost_LIBRARY_DIRS
        message(NOTICE "Boost found.")
        include_directories(${BOOST_INCLUDE_DIRS})
        link_directories(${Boost_LIBRARY_DIRS})
else()
        # Boost not found using configured path
        set(BOOST_ROOT "/opt/homebrew/Cellar/boost/1.85.0")
        message(WARNING "Boost not found. Attempting to use provided path ${BOOST_ROOT}")
        set(BOOST_INCLUDE_DIRS "${BOOST_ROOT}/include")
        set(BOOST_LIBRARY_DIRS "${BOOST_ROOT}/lib")
        include_directories(${BOOST_INCLUDE_DIRS})
        link_directories(${Boost_LIBRARY_DIRS})
endif()

add_executable(Uno++ Card/Card.hpp Card/Card.cpp Player/Player.hpp Player/Player.cpp Card/cardFunctions.hpp Game/gameFunctions.hpp Game/dataTypes.hpp Game/iterable_stack.hpp main.cpp)