#include <gtest/gtest.h>

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

TEST(GetResults, SameMovesAreADraw) {
    EXPECT_EQ(Game::getResults(ROCK, ROCK), 0);
    EXPECT_EQ(Game::getResults(PAPER, PAPER), 0);
    EXPECT_EQ(Game::getResults(SCISSORS, SCISSORS), 0);
}

TEST(GetResults, PlayerWins) {
    EXPECT_EQ(Game::getResults(ROCK, SCISSORS), 1);
    EXPECT_EQ(Game::getResults(PAPER, ROCK), 1);
    EXPECT_EQ(Game::getResults(SCISSORS, PAPER), 1);
}

TEST(GetResults, ComputerWins) {
    EXPECT_EQ(Game::getResults(ROCK, PAPER), -1);
    EXPECT_EQ(Game::getResults(PAPER, SCISSORS), -1);
    EXPECT_EQ(Game::getResults(SCISSORS, ROCK), -1);
}

// ---- toLower ----

TEST(ToLower, LowercasesEveryLetter) {
    EXPECT_EQ(Game::toLower("rOcK"), "rock");
    EXPECT_EQ(Game::toLower("ABC"), "abc");
    EXPECT_EQ(Game::toLower(""), "");
}

// ---- parseMove ----

TEST(ParseMove, AcceptsLettersAndWordsInAnyCase) {
    EXPECT_EQ(Game::parseMove("r"), ROCK);
    EXPECT_EQ(Game::parseMove("R"), ROCK);
    EXPECT_EQ(Game::parseMove("rock"), ROCK);
    EXPECT_EQ(Game::parseMove("ROCK"), ROCK);
    EXPECT_EQ(Game::parseMove("p"), PAPER);
    EXPECT_EQ(Game::parseMove("Paper"), PAPER);
    EXPECT_EQ(Game::parseMove("s"), SCISSORS);
    EXPECT_EQ(Game::parseMove("SciSSors"), SCISSORS);
}

TEST(ParseMove, RejectsAnythingElse) {
    EXPECT_FALSE(Game::parseMove("").has_value());
    EXPECT_FALSE(Game::parseMove("x").has_value());
    EXPECT_FALSE(Game::parseMove("rs").has_value());
    EXPECT_FALSE(Game::parseMove("rocks").has_value());
    EXPECT_FALSE(Game::parseMove("n").has_value());
}

// ---- validateGamesNumberInput ----

TEST(GameCount, ValidNumbers) {
    EXPECT_EQ(readGameCount("1\n"), 1);
    EXPECT_EQ(readGameCount("7\n"), 7);
    EXPECT_EQ(readGameCount("99\n"), 99);
}

TEST(GameCount, EnterOrEndOfInputGivesDefault) {
    EXPECT_EQ(readGameCount("\n"), Game::defaultGames);
    EXPECT_EQ(readGameCount(""), Game::defaultGames);
}

TEST(GameCount, BadInputIsRejectedThenAskedAgain) {
    EXPECT_EQ(readGameCount("0\n3\n"), 3);
    EXPECT_EQ(readGameCount("100\n3\n"), 3);
    EXPECT_EQ(readGameCount("-1\n3\n"), 3);
    EXPECT_EQ(readGameCount("abc\n3\n"), 3);
    EXPECT_EQ(readGameCount("5abc\n3\n"), 3);
    EXPECT_EQ(readGameCount("99999999999\n3\n"), 3); // used to crash
}

TEST(GameCount, RejectedInputPrintsInvalidInput) {
    FakeConsole console("abc\n3\n");
    std::string buffer;
    Game::validateGamesNumberInput(buffer);
    EXPECT_NE(console.output().find("Invalid input"), std::string::npos);
}