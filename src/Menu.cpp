#include "../headers/Menu.h"

void Menu::changeInput(char c) {
  userInput = c;
}

void Menu::display() {
   sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Surviland", sf::Style::Fullscreen);
   window.setFramerateLimit(60);

  sf::Font font;
  if (!font.loadFromFile("../fonts/Roboto-Black.ttf")) {
    // TODO throw exception
  }


  // game title
    sf::Text title("Surviland", font, 100);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(window.getSize().x / 2, window.getSize().y / 4);

    sf::Text playOption("Play (P)", font, 35);
    playOption.setOrigin(playOption.getLocalBounds().width / 2, playOption.getLocalBounds().height / 2);
    playOption.setPosition(window.getSize().x / 2, window.getSize().y / 2);

    sf::Text statsOption("Stats (S)", font, 35);
    statsOption.setOrigin(statsOption.getLocalBounds().width / 2, statsOption.getLocalBounds().height / 2);
    statsOption.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 60);

    while (window.isOpen()) {
        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
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
