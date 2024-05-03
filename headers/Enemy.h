#pragma once

#include "Entity.h"
#include "Game.h"

class Enemy : public Entity{
protected:
    int dmg;
    char dir;
    bool hit;
    bool lastHit;

public:
    Enemy(int x, int y, int hp, int dmg, char dir) : Entity(x, y, hp), dmg(dmg), dir(dir), hit(false), lastHit(false){}

    virtual void changeDirection(Board& board, Player& player) = 0;
    virtual void goBack(Board& board, Player& player) = 0;

    void modifyDirection(char newDir) {
        dir = newDir;
    }

//    [[nodiscard]] char getDir() const {
//        return dir;
//    }

    void activateHit() {
        lastHit = true;
    }

//    void undoHit() {
//        lastHit = false;
//    }

    [[nodiscard]] bool checkLastHit() const {
        return lastHit;
    }

    void hitEnemy(char symbol, int att1, int att2, bool spell) {
        hit = true;
        if (symbol == 'L') {
            hp-=att1; // ability
            if (spell) hp -= att2; // spellFeature1
        }
        else hp -= att2;
        if (hp <= 0) decreaseAttackDamage();
    }

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
    DumbEnemy(int x, int y, int hp, int dmg, char dir) : Enemy(x, y, hp, dmg, dir){}

    void changeDirection(Board& board, Player& player) override {
        std::cout << player.getMoney();
        if (dir == 'U' && x > 0) x--;
        if (dir == 'D' && x <= board.getHeight()) x++;
        if (dir == 'L' && y > 0) y--;
        if (dir == 'R' && y <= board.getWidth()) y++;
    }

    void goBack(Board& board, Player& player) override {
        std::cout << player.getMoney();
        if (dir == 'U' && x <= board.getHeight()) x++;
        if (dir == 'D' && x > 0) x--;
        if (dir == 'L' && y <= board.getWidth()) y++;
        if (dir == 'R' && y > 0) y--;
    }
};

class SmartEnemy : public Enemy{
private:
    int prevX{};
    int prevY{};

    void track(const Player& player) {
        prevX = x;
        prevY = y;

        int playerX = player.getX();
        int playerY = player.getY();

        if (x > playerX) x--;
        else if (x < playerX) x++;
        else {
            if (y > playerY) y--;
            else y++;
        }
    }

public:
    SmartEnemy(int x, int y, int hp, int dmg, char dir) : Enemy(x, y, hp, dmg, dir){}

    void changeDirection(Board& board, Player& player) override {
        std::cout << board.getWidth();
        track(player);
    }

    void goBack(Board& board, Player& player) override {
        std::cout << board.getWidth();
        std::cout << player.getMoney();
        x = prevX;
        y = prevY;
    }
};