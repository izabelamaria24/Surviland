
#pragma once
#include <SFML/Graphics.hpp>

#include "./GameTemplate.h"

class Menu : public GameTemplate<Menu> {
  friend class GameTemplate<Menu>;

  private:
    char userInput;  

    Menu() = default;

    void changeInput(char c);
    
  public:
    Menu& operator=(const Menu&) = delete;
    Menu(const Menu&) = delete;

    void init();
    
    void display();

    ~Menu() = default;
}
