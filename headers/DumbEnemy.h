#pragma once

#include "Enemy.h"

class DumbEnemy : public Enemy{
public:
    DumbEnemy(int x, int y, int hp, int dmg, char dir) : Enemy(x, y, hp, dmg, dir){}

    void changeDirection(Board& board, Player& player) override;
    void goBack(Board& board, Player& player) override;

    DumbEnemy(const DumbEnemy& other) = default;

    DumbEnemy& operator=(DumbEnemy other) noexcept {
        swap(*this, other);
        return *this;
    }

    friend void swap(DumbEnemy& e1, DumbEnemy& e2) {
        using std::swap;
        swap(static_cast<Enemy&>(e1), static_cast<Enemy&>(e2));
        swap(e1.dmg, e2.dmg);
        swap(e1.dir, e2.dir);
        swap(e1.hit, e2.hit);
        swap(e1.lastHit, e2.lastHit);
    }

    [[nodiscard]] std::shared_ptr<Enemy> clone() const override {
        return std::make_shared<DumbEnemy>(*this);
    }
};