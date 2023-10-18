cmake_minimum_required(VERSION 3.24)
project(battle_line)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/cards)
include_directories(include/piles)
include_directories(include/regions)

add_executable(battle_line
        main.cpp
        src/cards/TroopCard.cpp
        src/cards/TacticsCard.cpp
        src/Deck.cpp
        src/piles/Pile.cpp
        src/piles/TroopCardPile.cpp
        src/piles/TacticsCardPile.cpp
        src/piles/DiscardPile.cpp
        src/regions/Region.cpp
        src/Player.cpp
        src/regions/RegionsManager.cpp
        )
