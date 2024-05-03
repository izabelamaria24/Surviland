
#pragma once
#include "./GameTemplate.h"

class Menu : public GameTemplate<Menu> {
  friend class GameTemplate<Menu>;

  private:
    Menu() = default;

    static void handlePlay(sf::RenderWindow& window);
    static void display();
    
  public:
    Menu& operator=(const Menu&) = delete;
    Menu(const Menu&) = delete;

    static void init();

    ~Menu() override = default;
};
