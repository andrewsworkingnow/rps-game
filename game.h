#ifndef GAME_H
#define GAME_H

class Game
{
public:
    int getResults(char playerMove, char computerMove);
    char getComputerMove();
    char getPlayerMove();
	void run();
};

#endif // GAME_H
