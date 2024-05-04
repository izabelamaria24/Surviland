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
    Enemy(int x, int y, int hp, int dmg, char dir) : Entity(x, y, hp), dmg(dmg), dir(dir), hit(false), lastHit(false){}

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

    Enemy& operator=(Enemy&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    friend void swap(Enemy& e1, Enemy& e2) {
        using std::swap;
        swap(static_cast<Entity&>(e1), static_cast<Entity&>(e2));
        swap(e1.dmg, e2.dmg);
        swap(e1.dir, e2.dir);
        swap(e1.hit, e2.hit);
        swap(e1.lastHit, e2.lastHit);
    }

    [[nodiscard]] virtual std::shared_ptr<Enemy> clone() const = 0;
};