#include "../headers/Game.h"

void Game::clearScreen(sf::RenderWindow& window) {
    window.clear();
}

void Game::start(sf::RenderWindow& window) {
    window.setActive(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // TODO handle game events
        }
    }
}

void Game::render(sf::RenderWindow &window) {

}