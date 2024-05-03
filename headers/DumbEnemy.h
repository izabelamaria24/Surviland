#pragma once

#include "Enemy.h"

class DumbEnemy : public Enemy{
public:
    DumbEnemy(int x, int y, int hp, int dmg, char dir) : Enemy(x, y, hp, dmg, dir){}

    void changeDirection(Board& board, Player& player) override;
    void goBack(Board& board, Player& player) override;

    std::shared_ptr<Enemy> clone() const override {
        return std::make_shared<DumbEnemy>(*this);
    }
};