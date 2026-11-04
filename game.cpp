// C++ Program to Implement Rock-Paper-Scissors
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "game.h"
#include "messages.h"

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
            std::cout << "\t\t\tInvalid Player Move!!! Please Try Again." << std::endl;
        }
    }
    return playerMove;
}

// gameplay function
void Game::run()
{
    welcomeMessage();
    // computer move
    char computerMove = Game::getComputerMove();
    // player move
    char playerMove = Game::getPlayerMove();

    int result = Game::getResults(playerMove, computerMove);

    // priting result based on who won the game
    if (result == 0) {
        std::cout << "\n\t\t\tGame Draw!\n";
    }
    else if (result == 1) {
        std::cout << "\n\t\t\tCongratulations! Player won the "
            "game!\n";
    }
    else {
        std::cout << "\n\t\t\tOh! Computer won the game!\n";
    }

    // showing both  moves
    std::cout << "\t\t\tYour Move: " << playerMove << std::endl;
    std::cout << "\t\t\tComputer's Move: " << computerMove << std::endl;

}


