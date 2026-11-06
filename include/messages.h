#ifndef MESSAGES_H
#define MESSAGES_H

#include <game.h>
#include <iostream>
#include <string>

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
void printRoundResult(Move playerMove, Move computerMove);
void printFinalGameResult(int playerScore, int computerScore, const std::string &playerName);
const char *moveName(Move move);

#endif // MESSAGES_H
