#include "../headers/Menu.h"

void Menu::changeInput(char c) {``
  userInput = c;
} 

void Menu::displayMenu() {
   sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Surviland", sf::Style::Fullscreen);
   window.setFramerateLimit(60);
   
  sf::Font font;
  if (!font.loadFromFile(R"(fonts/Roboto-Black.ttf)")) {
    // TODO throw exception
  }
  
  sf::Text title("Surviland", font, 80);
  title.setFillColor(sf::Color::White);
  title.setStyle(sf::Text::Bold);
  title.setPosition(window.getSize().x / 2 - title.getGlobalBounds().width / 2, 100);
}

void Menu::init() { 
  displayMenu();
}
