
#pragma once

#include "GameTemplate.h"
#include "Game.h"

struct GameData;

class Menu : public GameTemplate<Menu> {
  friend class GameTemplate<Menu>;

  private:
    Menu() = default;

    static void handlePlay(sf::RenderWindow& window);
    static void handleStats(sf::RenderWindow& window);

    static void display();
    
  public:
    Menu& operator=(const Menu&) = delete;
    Menu(const Menu&) = delete;

    static void init();

    ~Menu() override = default;
};
