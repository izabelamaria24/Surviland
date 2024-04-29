#pragma once

#include "Entity.h"
#include "Game.h"

class Enemy : public Entity{
protected:
    int dmg;
    char dir;
    bool hit;

public:
    Enemy(int x, int y, int hp, int dmg, char dir) : Entity(x, y, hp), dmg(dmg), dir(dir), hit(false){}

    virtual void changeDirection(Board& board, Player& player) = 0;
    virtual void goBack(Board& board, Player& player) = 0;

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
    DumbEnemy(int x, int y, int hp, int dmg, char dir) : Enemy(x, y, hp, dmg, dir){}

    void changeDirection(Board& board, Player& player) override {
        if (dir == 'U' && x > 0) x--;
        if (dir == 'D' && x <= board.getHeight()) x++;
        if (dir == 'L' && y > 0) y--;
        if (dir == 'R' && y <= board.getWidth()) y++;
    }

    void goBack(Board& board, Player& player) override {
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

    void track(Player& player) {
        prevX = x;
        prevY = y;

        int playerX = player.getX();
        int playerY = player.getY();

        if (x > playerX) x--;
        else if (x < playerX) x++;
        else if (x == playerX) {
            if (y > playerY) y--;
            else y++;
        }
    }

public:
    SmartEnemy(int x, int y, int hp, int dmg, char dir) : Enemy(x, y, hp, dmg, dir){}

    void changeDirection(Board& board, Player& player) override {
        track(player);
    }

    void goBack(Board& board, Player& player) override {
        x = prevX;
        y = prevY;
    }
};