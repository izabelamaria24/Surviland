#pragma once

#include "./GameTemplate.h"
#include "Board.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"

#include <iostream>
#include <memory>

class Game : public GameTemplate<Game> {
  friend class GameTemplate<Game>;

private:
    bool gameOver = false;
    int time = 0;
    bool victory = false;
    std::string outputMessage;

    std::vector<std::shared_ptr<Enemy>>enemies;
    std::vector<std::shared_ptr<PowerUp>> powerUps;
    static Board board;
    static Player player;

    void render(sf::RenderWindow& window);

    std::pair<int, int> checkPlayerDirection();

    [[nodiscard]] bool checkVictory() const;

    void healEnemies();

    void collectMoney();
    void collectHP();
    void collectArmor();
    void collectStopwatch();
    void collectAllMoney();

    void changeEnemiesDirection();

    void markEnemies();
    void markPowerUps();

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

    void moveEnemies();

    void drawSpell();

    void clearSpell();

    void clearAttack();

    void markEntities();

    void collectResources();

    [[nodiscard]] bool checkCollision(int x, int y) const;

    static bool borders (int x, int y);

    ~Game() override = default;
};
