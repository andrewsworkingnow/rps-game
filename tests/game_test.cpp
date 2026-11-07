#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <iostream>
#include <sstream>
#include <string>

#include "game.h"

namespace {

// Feeds text to std::cin and hides std::cout output while it exists.
class FakeConsole {
  public:
    explicit FakeConsole(const std::string &input) : input_(input) {
        oldIn_ = std::cin.rdbuf(input_.rdbuf());
        oldOut_ = std::cout.rdbuf(output_.rdbuf());
        std::cin.clear();
    }
    ~FakeConsole() {
        std::cin.rdbuf(oldIn_);
        std::cout.rdbuf(oldOut_);
        std::cin.clear();
    }
    std::string output() const { return output_.str(); }

  private:
    std::istringstream input_;
    std::ostringstream output_;
    std::streambuf *oldIn_;
    std::streambuf *oldOut_;
};

int readGameCount(const std::string &typed) {
    FakeConsole console(typed);
    std::string buffer;
    return Game::validateGamesNumberInput(buffer);
}

} // namespace

// ---- getResults: 1 = player wins, -1 = computer wins, 0 = draw ----

TEST_CASE("getResults: same moves are a draw") {
    CHECK(Game::getResults(ROCK, ROCK) == 0);
    CHECK(Game::getResults(PAPER, PAPER) == 0);
    CHECK(Game::getResults(SCISSORS, SCISSORS) == 0);
}

TEST_CASE("getResults: player wins") {
    CHECK(Game::getResults(ROCK, SCISSORS) == 1);
    CHECK(Game::getResults(PAPER, ROCK) == 1);
    CHECK(Game::getResults(SCISSORS, PAPER) == 1);
}

TEST_CASE("getResults: computer wins") {
    CHECK(Game::getResults(ROCK, PAPER) == -1);
    CHECK(Game::getResults(PAPER, SCISSORS) == -1);
    CHECK(Game::getResults(SCISSORS, ROCK) == -1);
}

// ---- toLower ----

TEST_CASE("toLower: lowercases every letter") {
    CHECK(Game::toLower("rOcK") == "rock");
    CHECK(Game::toLower("ABC") == "abc");
    CHECK(Game::toLower("") == "");
}

// ---- parseMove ----

TEST_CASE("parseMove: accepts letters and words in any case") {
    CHECK(Game::parseMove("r") == ROCK);
    CHECK(Game::parseMove("R") == ROCK);
    CHECK(Game::parseMove("rock") == ROCK);
    CHECK(Game::parseMove("ROCK") == ROCK);
    CHECK(Game::parseMove("p") == PAPER);
    CHECK(Game::parseMove("Paper") == PAPER);
    CHECK(Game::parseMove("s") == SCISSORS);
    CHECK(Game::parseMove("SciSSors") == SCISSORS);
}

TEST_CASE("parseMove: rejects anything else") {
    CHECK_FALSE(Game::parseMove("").has_value());
    CHECK_FALSE(Game::parseMove("x").has_value());
    CHECK_FALSE(Game::parseMove("rs").has_value());
    CHECK_FALSE(Game::parseMove("rocks").has_value());
    CHECK_FALSE(Game::parseMove("n").has_value());
}

// ---- validateGamesNumberInput ----

TEST_CASE("game count: valid numbers") {
    CHECK(readGameCount("1\n") == 1);
    CHECK(readGameCount("7\n") == 7);
    CHECK(readGameCount("99\n") == 99);
}

TEST_CASE("game count: Enter or end of input gives the default") {
    CHECK(readGameCount("\n") == Game::defaultGames);
    CHECK(readGameCount("") == Game::defaultGames);
}

TEST_CASE("game count: bad input is rejected, then asked again") {
    CHECK(readGameCount("0\n3\n") == 3);
    CHECK(readGameCount("100\n3\n") == 3);
    CHECK(readGameCount("-1\n3\n") == 3);
    CHECK(readGameCount("abc\n3\n") == 3);
    CHECK(readGameCount("5abc\n3\n") == 3);
    CHECK(readGameCount("99999999999\n3\n") == 3); // used to crash
}

TEST_CASE("game count: rejected input prints Invalid input") {
    FakeConsole console("abc\n3\n");
    std::string buffer;
    Game::validateGamesNumberInput(buffer);
    CHECK(console.output().find("Invalid input") != std::string::npos);
}