#pragma once

#include "./GameTemplate.h"

class Game : public GameTemplate<Game> {
  friend class GameTemplate<Game>;

  private: 
    Game() = default;
    
    static bool gameOver;
    static int time;

    void render(sf::RenderWindow& window);
    
  public:
    Game& operator=(const Game&) = delete;
    Game(const Game&) = delete;

    void start(sf::RenderWindow& window); // TODO

    static void clearScreen(sf::RenderWindow& window);  // TODO

    ~Game() override = default;
};
