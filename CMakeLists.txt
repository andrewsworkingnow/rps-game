cmake_minimum_required(VERSION 3.16)
project(rps_game LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Game code shared by the game and the tests (everything except main)
add_library(rps_core src/game.cpp src/messages.cpp)
target_include_directories(rps_core PUBLIC include)
if(MSVC)
    target_compile_options(rps_core PRIVATE /W4)
endif()

add_executable(rps_game src/main.cpp)
target_link_libraries(rps_game PRIVATE rps_core)

enable_testing()
add_executable(rps_tests tests/game_test.cpp)
target_link_libraries(rps_tests PRIVATE rps_core)
add_test(NAME rps_tests COMMAND rps_tests)