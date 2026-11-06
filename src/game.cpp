// C++ Program to Implement Rock-Paper-Scissors
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>
#include "game.h"
#include "messages.h"

Game::Game() : playerName("Player1"), numGames(defaultGames), playerScore(0), computerScore(0) {}

// Function to return the result of the game
int Game::getResults(char playerMove, char computerMove)
{
    // condition for draw
    if (playerMove == computerMove) {
        return 0;
    }

    // condition for win and loss according to game rule
    if (playerMove == 's' && computerMove == 'p') {
        return 1;
    }
    if (playerMove == 's' && computerMove == 'r') {
        return -1;
    }
    if (playerMove == 'p' && computerMove == 'r') {
        return 1;
    }
    if (playerMove == 'p' && computerMove == 's') {
        return -1;
    }
    if (playerMove == 'r' && computerMove == 'p') {
        return -1;
    }
    if (playerMove == 'r' && computerMove == 's') {
        return 1;
    }

    return 0;
}

// get the computer move
char Game::getComputerMove()
{
    int move;
    // generating random number between 0 - 2
    srand(time(NULL));
    move = rand() % 3;

    // returning move based on the random number generated
    if (move == 0) {
        return 'p';
    }
    else if (move == 1) {
        return 's';
    }
    return 'r';
}


// get the player move
char Game::getPlayerMove()
{
    char playerMove;

    // input from the user
    while (1) {
        std::cin >> playerMove;
        if (playerMove == 'p' || playerMove == 'r' || playerMove == 's') {
            break;
        }
        else {
            printingPrompts(MessageType::INVALID_INPUT);
        }
    }
    return playerMove;
}
int Game::validateGamesNumberInput(std::string& input)
{
	while (true) {
		std::getline(std::cin, input);
		if (input.empty()) {
			return defaultGames; // Default value
		}
		try {
			int numGames = std::stoi(input);
			if (numGames >= minGames && numGames <= maxGames) {
				return numGames;
			}
			else {
				printingPrompts(MessageType::INVALID_INPUT);
				printingPrompts(MessageType::GAMES_NUMBER);
			}
		}
		catch (const std::invalid_argument&) {
			printingPrompts(MessageType::INVALID_INPUT);
			printingPrompts(MessageType::GAMES_NUMBER);
		}
	}
}
void Game::gameSetup()
{
    printingPrompts(MessageType::WELCOME);
    printingPrompts(MessageType::USER_NAME);
    std::string input;
	std::getline(std::cin, input);
    if (!input.empty()) {
		this->playerName = input;
    }
	printingPrompts(MessageType::GAMES_NUMBER);
    this->numGames = validateGamesNumberInput(input);

}
// gameplay function
void Game::run()
{
    
    Game::gameSetup();
    clearScreen();

    while (numGames > 0)
    {
        printingPrompts(MessageType::GAME_START);
        // get moves
        char computerMove = Game::getComputerMove();
        char playerMove = Game::getPlayerMove();

        int result = Game::getResults(playerMove, computerMove);

        // priting result based on who won the game
        if (result == 0) {
            printingPrompts(MessageType::GAME_DRAW);
			playerScore++;
			computerScore++;
        }
        else if (result == 1) {
            printingPrompts(MessageType::GAME_WON);
            playerScore++;
        }
        else {
            printingPrompts(MessageType::GAME_LOST);
			computerScore++;
        }
    
		printGameResult(playerMove, computerMove);
        numGames--;
    }
}


