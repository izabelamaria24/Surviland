#pragma once

#include "./GameTemplate.h"
#include "Board.h"
#include "Player.h"

class Game : public GameTemplate<Game> {
  friend class GameTemplate<Game>;

private:
    bool gameOver = false;
    int time = 0;
    bool victory = false;
    std::string outputMessage;

    void render(sf::RenderWindow& window);
    static Board board;
    static Player player;
    
  public:
    Game() = default;
    Game& operator=(const Game&) = delete;
    Game(const Game&) = delete;

    static Board& getBoard() {
        return board;
    }

    static Player& getPlayer() {
        return player;
    }

    static void build(const Board& initialBoard, const Player& initialPlayer) {
        board = initialBoard;
        player = initialPlayer;
    }

    void start(sf::RenderWindow& window); // TODO

    void clearScreen(sf::RenderWindow& window);  // TODO

    static bool borders (int x, int y);

    ~Game() override = default;
};
