cmake_minimum_required(VERSION 3.24)
project(battle_line)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/cards)
include_directories(include/piles)

add_executable(battle_line
        main.cpp
        src/cards/TroopCard.cpp
        src/cards/TacticsCard.cpp
        src/piles/Pile.cpp)
