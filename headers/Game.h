#pragma once

#include "Board.h"
#include "Controller.h"
#include "GameTemplate.h"
#include "EventData.h"
#include "Player.h"
#include "Portal.h"
#include "PowerUp.h"
#include "Parser.h"

#include <algorithm>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <string>

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
    std::vector<std::shared_ptr<Portal>> portals;
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

    void addPortal(const std::shared_ptr<Portal>& portal);
    void checkPortal();

    /// observers methods
    void addObservers();
    void notifyObservers(const EventData& eventData, const std::string& observerType);

    Board& getBoard();

    Player& getPlayer();

    void build(const Board& initialBoard, const Player& initialPlayer);

    void start(sf::RenderWindow& window);

    static void clearScreen(sf::RenderWindow& window);

    std::pair<int, int> checkPlayerDirection();

    void update();

    void win();

    void updateOutputMessage(const std::string& m);

    void addEnemy(const std::shared_ptr<Enemy>& newEnemy);

    void addPowerup(int x, int y, int hp, const std::string& type);

    void moveEnemies();

    void markPortals();

    void drawSpell();

    void clearSpell();

    void clearAttack();

    void markEntities();

    void markObstacles();

    void healEnemies();

    void changeEnemiesDirection();

    void takePowerups(int x, int y, char sym);

    void attackEnemies(int x, int y, char sym, bool& enemyFound, bool& stillAlive);

    void collectResources();

    [[nodiscard]] bool checkCollision(int x, int y) const;

    bool borders (int x, int y);

    static std::string getCurrentDate();

    ~Game() override = default;
};
