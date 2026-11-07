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
    Move getComputerMove();
    Move getPlayerMove();

  public:
    static constexpr int maxGames = 999;
    static constexpr int minGames = 1;
    static constexpr int defaultGames = 5;
    static int validateGamesNumberInput(std::string &input);
    static int getResults(Move playerMove, Move computerMove);
    static std::string toLower(const std::string &text);
    static std::optional<Move> parseMove(const std::string &text);

    Game();
    void run();
};

#endif // GAME_H
