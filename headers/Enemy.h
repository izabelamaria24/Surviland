#pragma once

#include "Entity.h"
#include "Game.h"

class Enemy : public Entity {
protected:
    int dmg;
    char dir;
    bool hit;
    bool lastHit;

public:
    Enemy(int x, int y) : Entity(x, y), dmg(0) {}
    Enemy(int x, int y, int hp, int dmg, char dir) : Entity(x, y, hp), dmg(dmg), dir(dir), hit(false), lastHit(false){
        if (dmg > 15) throw LogicError("Enemy dmg is too high!");
    }

    virtual void changeDirection(Board& board, Player& player) = 0;
    virtual void goBack(Board& board, Player& player) = 0;

    void modifyDirection(char newDir);

    void activateHit();

    [[nodiscard]] bool checkLastHit() const;

    void hitEnemy(char symbol, int att1, int att2, bool spell);

    void enemyRecover();

    [[nodiscard]] bool isHit() const;

    [[nodiscard]] bool isAlive() const;

    [[nodiscard]] int attackDamage() const;

    void decreaseAttackDamage();

    void moveOneStep(int x, int y);

    Enemy(const Enemy& other) = default;

    [[nodiscard]] virtual std::shared_ptr<Enemy> clone() const = 0;
};