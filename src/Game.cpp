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

        window.clear();
        render(window);
        window.display();
    }
}

void Game::render(sf::RenderWindow &window) {
  sf::Font font;
  if (!font.loadFromFile("../fonts/Roboto-Black.ttf")) {
    // TODO throw exception
  }

    // Load the background image
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../assets/hogrider.png")) {
        // TODO throw exception
    }

    sf::Texture dumbEnemyTexture;
    if (!dumbEnemyTexture.loadFromFile("../assets/hogrider.png")) {
        // TODO throw exception
    }

    sf::Texture smartEnemyTexture;
    if (!smartEnemyTexture.loadFromFile("")) {
        // TODO throw exception
    }

    sf::Texture spellTexture;
    if (!spellTexture.loadFromFile("../assets/spell.png")) {
        // TODO throw exception
    }

  const int cellSize = 100;
    for (int i = 0; i < board.getHeight(); ++i) {
        for (int j = 0; j < board.getWidth(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(i * cellSize, j * cellSize);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Red);
            cell.setFillColor(sf::Color::White);

            if (player.getX() == i && player.getX() == j)
                cell.setTexture(&playerTexture);
            window.draw(cell);
        }
    }
}

bool Game::borders(int x, int y) {
    return x >= 1 && x <= board.getWidth() && y >= 1 && y <= board.getHeight();
}

void Game::update() {
    while (player.updateAvailable()) {
        player.levelUp();
//        availableAbilityUpgrades++;
        player.payUpgrade();
    }
}

bool Game::checkVictory() const {
    return time >= 100;
}

void Game::win() {
    victory = true;
    outputMessage = "VICTORY!";
    gameOver = true;
    update();
}