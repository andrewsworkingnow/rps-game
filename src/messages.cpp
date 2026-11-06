#include "messages.h"
#include <conio.h>

void printingPrompts(MessageType messageType, const std::string &playerName) {

    switch (messageType) {
    case MessageType::WELCOME:
        std::cout << "Welcome to Rock-Paper-Scissors Game!" << std::endl;
        break;
    case MessageType::GAMES_NUMBER:
        std::cout << "Enter the number of games you want to play, Default is 5 press enter "
                     "to skip: ";
        break;
    case MessageType::USER_NAME:
        std::cout << "Enter your name, press enter to skip: ";
        break;
    case MessageType::INVALID_INPUT:
        std::cout << "Invalid input! Please try again." << std::endl;
        break;
    case MessageType::GAME_RESULT:
        std::cout << "\t\t\tGame result: ";
        break;
    case MessageType::GAME_WON:
        std::cout << "\t\t\tCongratulations! " << playerName << " won the round!" << std::endl;
        break;
    case MessageType::GAME_LOST:
        std::cout << "\t\t\tOh no! Computer won the round!" << std::endl;
        break;
    case MessageType::GAME_DRAW:
        std::cout << "\t\t\tIt's a draw!" << std::endl;
        break;
    case MessageType::PRESS_ANY_KEY:
        std::cout << "Press any key to continue..." << std::endl;
        break;
    case MessageType::GAME_START:
        std::cout << "Game started! Press R for Rock, P for Paper, S for Scissors: ";
        break;
    default:
        break;
    }
}

void clearScreen() {
    std::cout << "\033[2J\033[1;1H"; // ANSI escape code to clear the console screen
}

void waitForKey() {
    printingPrompts(MessageType::PRESS_ANY_KEY);
    std::cout << std::flush;
    _getch();
    std::cout << std::endl;
}

void printRoundResult(char playerMove, char computerMove) {
    printingPrompts(MessageType::GAME_RESULT);
    std::cout << "\t\t\tYour Move: " << playerMove << std::endl;
    std::cout << "\t\t\tComputer's Move: " << computerMove << std::endl;
    waitForKey();
    clearScreen();
}

void printFinalGameResult(int playerScore, int computerScore, const std::string &playerName) {
    std::cout << "\nFinal Result:\n";
    std::cout << " " << playerName << "'s Score: " << playerScore << std::endl;
    std::cout << "Computer Score: " << computerScore << std::endl;
    if (playerScore > computerScore) {
        std::cout << "Congratulations! " << playerName << " won the Match!" << std::endl;
    } else if (playerScore < computerScore) {
        std::cout << "Oh no! Computer won the Match!" << std::endl;
    } else {
        std::cout << "It's a draw!" << std::endl;
    }
}
