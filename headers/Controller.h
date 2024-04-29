#pragma once

#include <string>

class Game;
class Observer {
protected:
    Game& game;
public:
    explicit Observer(Game& game) : game(game){}

    virtual void update(const std::string& event) = 0;
};

class PlayerController : public Observer {
private:
    void move();
    void attack();
    void upgrade();

public:
    explicit PlayerController(Game& game) : Observer(game){}

    void update(const std::string& event) override {
        if (event == "ATT")
            attack();
        if (event == "M")
            move();
        if (event == "UP")
            upgrade();
    }
};

class EnemyController : public Observer {
private:
    void spawnDumbEnemy();
    void spawnSmartEnemy();
    void spawnDumbEnemyHoard();
    void spawnSmartEnemyHoard();

public:
    EnemyController(Game& game) : Observer(game){}

    void update(const std::string& event) override {
        // TODO
    }
};

class PowerUpController : public Observer {
private:
    void spawnPowerup();

public:
    PowerUpController(Game& game) : Observer(game){}

    void update(const std::string& event) override {
        spawnPowerup();
    }
};