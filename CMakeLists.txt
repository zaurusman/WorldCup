cmake_minimum_required(VERSION 3.23)
project(WorldCup)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(WorldCup
        AVLTree.cpp
        AVLTree.h
        main23a1.cpp
        wet1util.h
        worldcup23a1.cpp
        worldcup23a1.h
        player.cpp
        player.h
        Team.cpp
        Team.h)
