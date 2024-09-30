#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Computer.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void checkWin();
    void resetBoard();

    sf::RenderWindow window;
    sf::Font font;
    sf::Text grid[3][3];
    sf::Text message;

    int board[3][3];
    bool playerTurn;
    bool gameOver;
    Computer computer;
};

#endif
