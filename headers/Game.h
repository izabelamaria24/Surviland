#pragma once

#include "./GameTemplate.h"
#include "Board.h"
#include "Player.h"
#include "Enemy.h"
#include "PowerUp.h"
#include "EventData.h"
//#include "Controller.h"

#include <iostream>
#include <memory>

class Game : public GameTemplate<Game> {
  friend class GameTemplate<Game>;

private:
//    std::vector<std::shared_ptr<Observer>> observers;

    bool gameOver = false;
    int time = 0;
    bool victory = false;
    std::string outputMessage;

    std::vector<std::shared_ptr<Enemy>>enemies;
    std::vector<std::shared_ptr<PowerUp>> powerUps;
    Board board;
    Player player;

    void render(sf::RenderWindow& window);

    [[nodiscard]] bool checkVictory() const;

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

    Board& getBoard() {
        return board;
    }

    Player& getPlayer() {
        return player;
    }

    void build(const Board& initialBoard, const Player& initialPlayer) {
        board = initialBoard;
        player = initialPlayer;
    }

    void start(sf::RenderWindow& window); // TODO

    void clearScreen(sf::RenderWindow& window);  // TODO

    std::pair<int, int> checkPlayerDirection();

    void update();

    void win();

    void addEnemy(int x, int y, int dmg, int hp, char dir, int type);

    void addPowerup(int x, int y, int hp, std::string& type);

    void moveEnemies();

    void drawSpell();

    void clearSpell();

    void clearAttack();

    void markEntities();

    void healEnemies();

    void takePowerups(int x, int y, char sym);

    void attackEnemies(int x, int y, char sym, bool& enemyFound, bool& stillAlive);


    void collectResources();

    void resetHit();

    [[nodiscard]] bool checkCollision(int x, int y) const;

    bool borders (int x, int y);

    ~Game() override = default;
};
