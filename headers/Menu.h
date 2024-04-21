
#pragma once
#include "./GameTemplate.h"

class Menu : public GameTemplate<Menu> {
  friend class GameTemplate<Menu>;

  private:
    Menu() = default;

    void handlePlay(sf::RenderWindow& window);
    void display();
    
  public:
    Menu& operator=(const Menu&) = delete;
    Menu(const Menu&) = delete;

    void init();

    ~Menu() override = default;
};
