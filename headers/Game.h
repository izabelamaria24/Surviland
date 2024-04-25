#pragma once

#include "./GameTemplate.h"
#include "Board.h"
#include "Player.h"

class Game : public GameTemplate<Game> {
  friend class GameTemplate<Game>;

private:
    Board board;
    Player player;
    bool gameOver = false;
    int time = 0;
    bool victory = false;
    std::string outputMessage;

    void render(sf::RenderWindow& window);
    
  public:
    Game() = default;
    Game& operator=(const Game&) = delete;
    Game(const Game&) = delete;

    void build(const Board& initialBoard, const Player& initialPlayer) {
        board = initialBoard;
        player = initialPlayer;
    }

    void start(sf::RenderWindow& window); // TODO

    void clearScreen(sf::RenderWindow& window);  // TODO

    ~Game() override = default;
};
