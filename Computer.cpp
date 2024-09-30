#include "Computer.h"
#include <iostream>

void Computer::makeMove(int board[3][3], sf::Text grid[3][3]) {
    int row, col;
    findBestMove(board, row, col);
    board[row][col] = 2; // Computer move
    grid[row][col].setString("O");
}

void Computer::findBestMove(int board[3][3], int& bestRow, int& bestCol) {
    int bestVal = -1000;
    bestRow = -1;
    bestCol = -1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0) {
                board[i][j] = 2; // Try the move
                int moveVal = minimax(board, false); // Evaluate the move
                board[i][j] = 0; // Undo the move

                if (moveVal > bestVal) {
                    bestRow = i;
                    bestCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

int Computer::evaluate(int board[3][3]) {
    // Check rows
    for (int row = 0; row < 3; ++row) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == 2)
                return 10; // Computer wins
            else if (board[row][0] == 1)
                return -10; // Player wins
        }
    }

    // Check columns
    for (int col = 0; col < 3; ++col) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == 2)
                return 10; // Computer wins
            else if (board[0][col] == 1)
                return -10; // Player wins
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == 2)
            return 10; // Computer wins
        else if (board[0][0] == 1)
            return -10; // Player wins
    }
    
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == 2)
            return 10; // Computer wins
        else if (board[0][2] == 1)
            return -10; // Player wins
    }

    return 0; // No winner yet
}

bool Computer::isMovesLeft(int board[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0) // An empty spot is available
                return true;
        }
    }
    return false; // No moves left
}


int Computer::minimax(int board[3][3], bool isComputerTurn) {
    int score = evaluate(board); // Evaluate the board
    if (score == 10 || score == -10) // If someone has won
        return score;
    if (isMovesLeft(board) == false) // If the board is full
        return 0;

    if (isComputerTurn) {
        int best = -1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 0) { // If the spot is available
                    board[i][j] = 2; // Make the computer's move
                    best = std::max(best, minimax(board, false)); // Recur for the player
                    board[i][j] = 0; // Undo the move
                }
            }
        }
        return best;
    } else {
        int best = 1000;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                if (board[i][j] == 0) { // If the spot is available
                    board[i][j] = 1; // Make the player's move
                    best = std::min(best, minimax(board, true)); // Recur for the computer
                    board[i][j] = 0; // Undo the move
                }
            }
        }
        return best;
    }
}

