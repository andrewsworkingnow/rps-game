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
void printingPrompts(MessageType messageType);
void clearScreen();
void waitForKey();
void printGameResult(char playerMove, char computerMove);

#endif // MESSAGES_H
