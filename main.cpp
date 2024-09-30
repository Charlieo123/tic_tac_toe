#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Computer.h"


int main() {
    sf::RenderWindow window(sf::VideoMode(600, 600), "Tic-Tac-Toe Home");
    
    sf::Font font;
    if (!font.loadFromFile("fonts/arial.ttf")) {
        return -1;
    }

    sf::Text title("Tic-Tac-Toe", font, 50);
    title.setPosition(150, 100);

    sf::Text startButton("Start Game", font, 30);
    startButton.setPosition(200, 300);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (startButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
                    window.close();
                    Game game;
                    game.run();
                }
            }
        }

        window.clear();
        window.draw(title);
        window.draw(startButton);
        window.display();
    }

    return 0;
}
