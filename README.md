# rps-game

A console Rock-Paper-Scissors game in C++20. Play 1 to 99 rounds against the
computer and see who wins the match.

## How to play
1. Enter your name, or press Enter to play as `Player1`.
2. Enter how many rounds to play, or press Enter for 5.
3. Each round, type your move and press Enter:
   - `R` or `Rock`
   - `P` or `Paper`
   - `S` or `Scissors`

   Moves work in any letter case.
4. After each round, press any key to continue.
5. When all rounds are played, the final score and the match winner are shown.

## Rules
- Rock beats Scissors, Scissors beats Paper, and Paper beats Rock.
- A round win gives the winner one point.
- A draw gives both you and the computer one point.

## Requirements
- Windows
- CMake 3.16 or newer
- A C++20 compiler, such as MSVC or MinGW-w64

## Build and run
```
cmake -S . -B build
cmake --build build --config Debug
build\Debug\rps_game.exe
```

## Run the tests
The tests use [doctest](https://github.com/doctest/doctest), which is included
as `tests/doctest.h`. After building:

```
ctest --test-dir build -C Debug --output-on-failure
```

To see each failed check in detail, run `build\Debug\rps_tests.exe` directly.

The tests cover:
- the result of every move combination
- reading moves, including capital letters and full words
- reading the number of rounds, including bad input such as `abc`, `5abc` and
  `99999999999`

## Project layout
```
include/   game.h, messages.h
src/       game.cpp (rules and game flow), messages.cpp (screen text), main.cpp
tests/     game_test.cpp, doctest.h
CMakeLists.txt
```