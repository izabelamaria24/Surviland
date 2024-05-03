#pragma once

#include "Enemy.h"

class SmartEnemy : public Enemy {
private:
    int prevX{};
    int prevY{};

    void track(const Player& player);

public:
    SmartEnemy(int x, int y, int hp, int dmg, char dir) : Enemy(x, y, hp, dmg, dir){}

    void changeDirection(Board& board, Player& player) override;

    void goBack(Board& board, Player& player) override;
};
