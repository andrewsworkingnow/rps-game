#ifndef MESSAGES_H
#define MESSAGES_H

#include <iostream>

enum class MessageType {
    WELCOME,
    GAMES_NUMBER,
    USER_NAME,
    INVALID_INPUT,
    GAME_RESULT,
    PRESS_ANY_KEY,
    GAME_WON,
    GAME_LOST,
    GAME_DRAW,
    GAME_START
};
void printingPrompts(MessageType messageType, const std::string &playerName = "");
void clearScreen();
void waitForKey();
void printRoundResult(char playerMove, char computerMove);
void printFinalGameResult(int playerScore, int computerScore, const std::string &playerName);

#endif // MESSAGES_H
