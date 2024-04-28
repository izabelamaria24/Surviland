#pragma once

#include "Entity.h"
#include "Game.h"

class Enemy : public Entity{
protected:
    int dmg;
    char dir;
    bool hit;

public:
    virtual void changeDirection() = 0;
    virtual void goBack() = 0;

    void modifyDirection(char newDir) {
        dir = newDir;
    }

    [[nodiscard]] char getDir() const {
        return dir;
    }

//    void hitEnemy(char symbol) {
//        hit = true;
//        if (symbol == 'L') {
//            hp-=ability;
//            if (unlockedSpell) hp -= spellFeature1;
//        }
//        else hp -= spellFeature1;
//        if (hp <= 0) decreaseAttackDamage();
//    }

    void enemyRecover() {
        hit = false;
    }

    [[nodiscard]] bool isHit() const {
        return hit;
    }

    [[nodiscard]] bool isAlive() const {
        return hp > 0;
    }

    [[nodiscard]] int attackDamage() const {
        return dmg;
    }

    void decreaseAttackDamage() {
        dmg = 0;
    }

};

class DumbEnemy : public Enemy{
public:
    void changeDirection() override {
        int height = Game::getBoard().getHeight();
        int width = Game::getBoard().getWidth();

        if (dir == 'U' && x > 0) x--;
        if (dir == 'D' && x <= height) x++;
        if (dir == 'L' && y > 0) y--;
        if (dir == 'R' && y <= width) y++;
    }

    void goBack() override {
        int height = Game::getBoard().getHeight();
        int width = Game::getBoard().getWidth();

        if (dir == 'U' && x <= height) x++;
        if (dir == 'D' && x > 0) x--;
        if (dir == 'L' && y <= width) y++;
        if (dir == 'R' && y > 0) y--;
    }
};

class SmartEnemy : public Enemy{
private:
    int prevX{};
    int prevY{};

    void track() {
        prevX = x;
        prevY = y;

        int playerX = Game::getPlayer().getX();
        int playerY = Game::getPlayer().getY();

        if (x > playerX) x--;
        else if (x < playerX) x++;
        else if (x == playerX) {
            if (y > playerY) y--;
            else y++;
        }
    }

public:
    SmartEnemy() = default;

    void changeDirection() override {
        track();
    }

    void goBack() override {
        x = prevX;
        y = prevY;
    }
};