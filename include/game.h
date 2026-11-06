#ifndef GAME_H
#define GAME_H

class Game {
  private:
    static constexpr int maxGames = 99;
    static constexpr int minGames = 1;
    static constexpr int defaultGames = 5;
    std::string playerName;
    int numGames;
    int playerScore;
    int computerScore;

  public:
    Game();
    void gameSetup();
    int validateGamesNumberInput(std::string &input);
    int getResults(char playerMove, char computerMove);
    char getComputerMove();
    char getPlayerMove();
    void run();
};

#endif // GAME_H
