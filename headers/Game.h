#pragma once

#include "GameTemplate.h"
#include "Board.h"
#include "Player.h"
#include "PowerUp.h"
#include "EventData.h"
#include "Controller.h"
#include "Exceptions.h"

#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <chrono>
#include <algorithm>

class Enemy;
class DumbEnemy;
class SmartEnemy;

class Game : public GameTemplate<Game> {
  friend class GameTemplate<Game>;

private:
    std::vector<std::shared_ptr<Observer>> observers;

    bool gameOver;
    int time = 0;
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

    void markEnemies();
    void markPowerUps();

    std::pair<int, int> generateCoordinates();
    static std::pair<int, int> generateEnemyAttributes();
    static void generateDirection(EventData& eventData);
    void generate(EventData& eventData);
    static void renderVictory(sf::RenderWindow& window);
    static void renderLose(sf::RenderWindow& window);

    std::shared_ptr<Enemy> checkEnemy(int x, int y);

public:
    Game() : gameOver(false) {
        addObservers();
    }

    Game& operator=(const Game&) = delete;
    Game(const Game&) = delete;

    void spawn();

    /// observers methods
    void addObservers();
    void notifyObservers(EventData& eventData, const std::string& observerType);

    Board& getBoard();

    Player& getPlayer();

    void build(const Board& initialBoard, const Player& initialPlayer);

    void start(sf::RenderWindow& window);

    static void clearScreen(sf::RenderWindow& window);

    std::pair<int, int> checkPlayerDirection();

    void update();

    void win();

    void updateOutputMessage(const std::string& m);

    void addEnemy(std::shared_ptr<Enemy>);

    void addPowerup(int x, int y, int hp, const std::string& type);

    void moveEnemies();

    void drawSpell();

    void clearSpell();

    void clearAttack();

    void markEntities();

    void healEnemies();

    void changeEnemiesDirection();

    void takePowerups(int x, int y, char sym);

    void attackEnemies(int x, int y, char sym, bool& enemyFound, bool& stillAlive);

    void collectResources();

    [[nodiscard]] bool checkCollision(int x, int y) const;

    bool borders (int x, int y);

    ~Game() override = default;
};
