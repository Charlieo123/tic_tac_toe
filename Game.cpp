#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(600, 600), "Tic-Tac-Toe Game"), playerTurn(true), gameOver(false) {
    font.loadFromFile("fonts/arial.ttf");

    // Initialize board and text
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = 0; // 0 means empty, 1 means player, 2 means computer
            grid[i][j].setFont(font);
            grid[i][j].setString("");
            grid[i][j].setCharacterSize(80);
            grid[i][j].setPosition(200 * j + 75, 200 * i + 50);
            grid[i][j].setFillColor(sf::Color::Blue);
        }
    }

    message.setFont(font);
    message.setCharacterSize(30);
    message.setPosition(150, 650); // Place the message below the grid
    message.setFillColor(sf::Color::Black);
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();

        if (!gameOver && playerTurn && event.type == sf::Event::MouseButtonPressed) {
            sf::Vector2i pos = sf::Mouse::getPosition(window);

            int row = pos.y / 200;
            int col = pos.x / 200;

            if (row < 3 && col < 3 && board[row][col] == 0) {
                board[row][col] = 1; // Player move
                grid[row][col].setString("X");
                checkWin();
                if (!gameOver) {
                    playerTurn = false;
                    computer.makeMove(board, grid);
                    checkWin();
                    playerTurn = true;
                }
            }
        }
    }
}

void Game::update() {
    if (gameOver && sf::Event::MouseButtonPressed) {
        resetBoard();
    }
}

void Game::render() {
    window.clear();
    sf::Vertex lines[8];
    // Horizontal lines
    lines[0] = sf::Vertex(sf::Vector2f(200, 0), sf::Color::White);
    lines[1] = sf::Vertex(sf::Vector2f(200, 600), sf::Color::White);
    lines[2] = sf::Vertex(sf::Vector2f(400, 0), sf::Color::White);
    lines[3] = sf::Vertex(sf::Vector2f(400, 600), sf::Color::White);

    // Vertical lines
    lines[4] = sf::Vertex(sf::Vector2f(0, 200), sf::Color::White);
    lines[5] = sf::Vertex(sf::Vector2f(600, 200), sf::Color::White);
    lines[6] = sf::Vertex(sf::Vector2f(0, 400), sf::Color::White);
    lines[7] = sf::Vertex(sf::Vector2f(600, 400), sf::Color::White);
    
    window.draw(lines, 8, sf::Lines);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            window.draw(grid[i][j]); // Draw each grid element
        }
    }

    window.draw(message); // Draw the message at the end
    window.display();
}


void Game::checkWin() {
    // Check rows and columns
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != 0) {
            gameOver = true;
            message.setString((board[i][0] == 1) ? "Player Wins!" : "Computer Wins!");
            return;
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != 0) {
            gameOver = true;
            message.setString((board[0][i] == 1) ? "Player Wins!" : "Computer Wins!");
            return;
        }
    }

    // Check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != 0) {
        gameOver = true;
        message.setString((board[0][0] == 1) ? "Player Wins!" : "Computer Wins!");
        return;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != 0) {
        gameOver = true;
        message.setString((board[0][2] == 1) ? "Player Wins!" : "Computer Wins!");
        return;
    }

    // Check for draw
    bool boardFull = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (board[i][j] == 0) {
                boardFull = false;
                break;
            }
        }
    }

    if (boardFull) {
        gameOver = true;
        message.setString("It's a Draw!");
    }
}


void Game::resetBoard() {
    // Reset the board and text for a new game
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            board[i][j] = 0; // Set all cells to empty
            grid[i][j].setString(""); // Clear the grid display
        }
    }

    playerTurn = true;   // Player starts first
    gameOver = false;    // Game is no longer over
    message.setString(""); // Clear the win/draw message
}

