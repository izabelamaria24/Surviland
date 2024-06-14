#include "../headers/Menu.h"
#include "../headers/Game.h"

void Menu::handlePlay(sf::RenderWindow& window) {
    Board board(10, 10);
    Player player(board.getHeight()  / 2, board.getWidth() / 2, 10, 0);

    std::shared_ptr<Game> game = Game::getGameInstance();

    game->build(board, player);
    game->start(window);
}

void Menu::display() {
   sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Surviland", sf::Style::Fullscreen);
   window.setFramerateLimit(60);

  sf::Font font;
  if (!font.loadFromFile("../fonts/Roboto-Black.ttf")) {
     throw FontError("Could not load menu font!");
  }

  // game title
    sf::Text title("Surviland", font, 100);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 4);

    sf::Text playOption("Play (P)", font, 35);
    playOption.setOrigin(playOption.getLocalBounds().width / 2, playOption.getLocalBounds().height / 2);
    playOption.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);

    sf::Text statsOption("Stats (S)", font, 35);
    statsOption.setOrigin(statsOption.getLocalBounds().width / 2, statsOption.getLocalBounds().height / 2);
    statsOption.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2 + 60);

    while (window.isOpen()) {
        // Handle events
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    handlePlay(window);
                    return;
                } else if (event.key.code == sf::Keyboard::S) {
                    // TODO STATS
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        // Clear the window
        window.clear();

        // Draw the title text
        window.draw(title);
        window.draw(playOption);
        window.draw(statsOption);

        // Display the contents of the window
        window.display();
    }
}

void Menu::init() { 
  display();
}
