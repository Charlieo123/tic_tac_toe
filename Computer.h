#ifndef COMPUTER_H
#define COMPUTER_H

#include <SFML/Graphics.hpp>

class Computer {
public:
    void makeMove(int board[3][3], sf::Text grid[3][3]);

private:
    void findBestMove(int board[3][3], int& row, int& col);
    int minimax(int board[3][3], bool isComputerTurn);
    int evaluate(int board[3][3]);
    bool isMovesLeft(int board[3][3]);
};

#endif
