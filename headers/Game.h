#pragma once

#include "./GameTemplate.h"

class Game : public GameTemplate<Game> {
  friend class GameTemplate<Game>;

  private: 
    Game() = default;
    
    static bool gameOver;
    static int time;
    
  public:
    Game& operator=(const Game&) = delete;
    Game(const Game&) = delete;

    void play();

    ~Game() = default;
}
