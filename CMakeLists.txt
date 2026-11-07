cmake_minimum_required(VERSION 3.16)
project(rps_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(rps_game
    src/main.cpp
    src/game.cpp
    src/messages.cpp
)
target_include_directories(rps_game PRIVATE include)