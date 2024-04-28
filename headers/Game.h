#pragma once

#include "./GameTemplate.h"
#include "Board.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"

#include <iostream>

class Game : public GameTemplate<Game> {
  friend class GameTemplate<Game>;

private:
    bool gameOver = false;
    int time = 0;
    bool victory = false;
    std::string outputMessage;

    std::vector<Enemy>enemies;
    std::vector<PowerUp> powerUps;
    static Board board;
    static Player player;

    void render(sf::RenderWindow& window);
    [[nodiscard]] bool checkVictory() const;
    
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

    void update();

    void win();

    void markEnemies();

    void moveEnemies();

    void clearSpell();

    bool checkCollision(int x, int y) const;

    static bool borders (int x, int y);

    ~Game() override = default;
};
