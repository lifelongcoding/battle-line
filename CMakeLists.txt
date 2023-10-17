cmake_minimum_required(VERSION 3.24)
project(battle_line C)

set(CMAKE_C_STANDARD 11)

include_directories(.)
include_directories(include)
include_directories(include/cards)

add_executable(battle_line
        include/cards/Card.h
        include/cards/TacticsCard.h
        include/cards/TroopCard.h)
