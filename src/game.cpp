#include "game.h"
#include "messages.h"
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <stdexcept>
#include <iostream>

Game::Game() : playerName("Player1"), numGames(defaultGames), playerScore(0), computerScore(0) {}

// Returns a lowercase copy, so "rOcK" becomes "rock".
std::string Game::toLower(const std::string &text) {
    std::string result;
    for (char c : text) {
        result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    }
    return result;
}

std::optional<Move> Game::parseMove(const std::string &text) {
    const std::string input = toLower(text);
    if (input == "r" || input == "rock") {
        return Move::ROCK;
    }
    if (input == "p" || input == "paper") {
        return Move::PAPER;
    }
    if (input == "s" || input == "scissors") {
        return Move::SCISSORS;
    }
    return std::nullopt; // not a move
}

// Function to return the result of the game
int Game::getResults(Move playerMove, Move computerMove) {
    // condition for draw
    if (playerMove == computerMove) {
        return 0;
    }

    // condition for win and loss according to game rule
    if (playerMove == Move::SCISSORS && computerMove == Move::PAPER) {
        return 1;
    }
    if (playerMove == Move::SCISSORS && computerMove == Move::ROCK) {
        return -1;
    }
    if (playerMove == Move::PAPER && computerMove == Move::ROCK) {
        return 1;
    }
    if (playerMove == Move::PAPER && computerMove == Move::SCISSORS) {
        return -1;
    }
    if (playerMove == Move::ROCK && computerMove == Move::SCISSORS) {
        return 1;
    }
    if (playerMove == Move::ROCK && computerMove == Move::PAPER) {
        return -1;
    }

    return 0;
}

// get the computer move
Move Game::getComputerMove() {
    int move;
    // generating random number between 0 - 2
    srand(time(NULL));
    move = rand() % 3;

    // returning move based on the random number generated
    if (move == 0) {
        return Move::PAPER;
    } else if (move == 1) {
        return Move::SCISSORS;
    }
    return Move::ROCK;
}

// get the player move
Move Game::getPlayerMove() {
    std::string line;
    while (std::getline(std::cin, line)) {
        const std::optional<Move> move = parseMove(line);
        if (move) {
            return *move;
        }
        printingPrompts(MessageType::INVALID_INPUT);
        printingPrompts(MessageType::GAME_START);
    }
    return Move::NA; // input ended (for example Ctrl+Z); fixed properly in a later step
}

int Game::validateGamesNumberInput(std::string &input) {
    while (true) {
        if (!std::getline(std::cin, input)) {
            return defaultGames; // input ended, for example Ctrl+Z
        }
        if (input.empty()) {
            return defaultGames;
        }

        try {
            std::size_t used = 0; // how many characters stoi read
            const int count = std::stoi(input, &used);
            if (used == input.size() && count >= minGames && count <= maxGames) {
                return count;
            }
        } catch (const std::invalid_argument &) { // not a number, like "abc"
        } catch (const std::out_of_range &) {     // too big, like "99999999999"
        }

        printingPrompts(MessageType::INVALID_INPUT);
        printingPrompts(MessageType::GAMES_NUMBER);
    }
}
void Game::gameSetup() {
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
void Game::run() {

    gameSetup();
    clearScreen();

    while (numGames > 0) {
        printingPrompts(MessageType::GAME_START);
        // get moves
        Move computerMove = getComputerMove();
        Move playerMove = getPlayerMove();
        if (playerMove == Move::NA) {
            printingPrompts(MessageType::INVALID_INPUT);
            break; // input ended
        }
        int result = getResults(playerMove, computerMove);

        // priting result based on who won the game
        if (result == 0) {
            printingPrompts(MessageType::GAME_DRAW);
            playerScore++;
            computerScore++;
        } else if (result == 1) {
            printingPrompts(MessageType::GAME_WON, playerName);
            playerScore++;
        } else {
            printingPrompts(MessageType::GAME_LOST);
            computerScore++;
        }

        printRoundResult(playerMove, computerMove);
        numGames--;
    }
    printFinalGameResult(playerScore, computerScore, playerName);
}
