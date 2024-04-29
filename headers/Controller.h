#pragma once

#include <string>
#include "Game.h"

class Observer {
protected:
    Game& game;
public:
    explicit Observer(Game& game) : game(game){}

    virtual void update(EventData& eventData) = 0;
};

class PlayerController : public Observer {
private:
    void move(EventData& eventData);
    void attack(EventData& eventData);
    void upgrade(EventData& eventData);

public:
    explicit PlayerController(Game& game) : Observer(game){}

    void update(EventData& eventData) override {
        if (eventData.name == "ATT")
            attack(eventData);
        if (eventData.name == "M")
            move(eventData);
        if (eventData.name == "UP")
            upgrade(eventData);
    }
};

class EnemyController : public Observer {
private:

    void spawnDumbEnemy(EventData& eventData) {
        game.moveEnemies();
        game.addEnemy(eventData.x + 1, eventData.y + 1, eventData.dmg, eventData.hp, eventData.dir, 1);
        game.markEntities();
    }

    void spawnSmartEnemy(EventData& eventData) {
        game.moveEnemies();
        game.addEnemy(eventData.x + 1, eventData.y + 1, eventData.dmg, eventData.hp, game.getBoard().getPlayer(game.getPlayer()), 2);
        game.markEntities();
    }
    void spawnDumbEnemyHoard(EventData& eventData) {
        game.moveEnemies();
        int xSwf = eventData.x, ySwf = eventData.y;
        for (int i = 1; i <= 3; i++) {
            game.addEnemy(xSwf + 1, ySwf + 1, eventData.dmg, eventData.hp, eventData.dir, 1);
            ySwf++;
        }
        game.clearAttack();
        game.markEntities();
    }

    void spawnSmartEnemyHoard(EventData& eventData) {
        game.moveEnemies();

        int height = game.getBoard().getHeight();
        int width = game.getBoard().getWidth();

        const int coordX[] = {1, 1, height, height};
        const int coordY[] = {width, 1, width, 1};

        for (int coord = 0; coord < 4; coord++)
            game.addEnemy(coordX[coord], coordY[coord], eventData.dmg, eventData.hp, game.getBoard().getPlayer(game.getPlayer()), 2);

        game.clearAttack();
        game.markEntities();
    }

public:
    explicit EnemyController(Game& game) : Observer(game){}

    void update(EventData& eventData) override {
        if (eventData.name == "SF") {
           spawnDumbEnemy(eventData);
        }

        if (eventData.name == "ST") {
            spawnSmartEnemy(eventData);
        }

        if (eventData.name == "SWF") {
            spawnDumbEnemyHoard(eventData);
        }

        if (eventData.name == "SWT") {
            spawnSmartEnemyHoard(eventData);
        }
    }
};

class PowerUpController : public Observer {
private:
    void spawnPowerup(EventData& eventData) {
        game.moveEnemies();
        game.addPowerup(eventData.x + 1, eventData.y + 1, eventData.hp, eventData.type);
        game.clearAttack();
        game.markEntities();
    }

public:
    explicit PowerUpController(Game& game) : Observer(game){}

    void update(EventData& eventData) override {
        spawnPowerup(eventData);
    }
};