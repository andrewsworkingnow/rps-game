#ifndef GAME_H
#define GAME_H

#include <optional>
#include <string>

enum Move { ROCK = 'r', PAPER = 'p', SCISSORS = 's', NA = 'n' };

class Game {
  private:
    std::string playerName;
    int numGames;
    int playerScore;
    int computerScore;
    void gameSetup();
    int validateGamesNumberInput(std::string &input);
    int getResults(Move playerMove, Move computerMove);
    std::string toLower(const std::string &text);
    std::optional<Move> parseMove(const std::string &text);
    Move getComputerMove();
    Move getPlayerMove();

  public:
    static constexpr int maxGames = 99;
    static constexpr int minGames = 1;
    static constexpr int defaultGames = 5;

    Game();
    void run();
};

#endif // GAME_H
