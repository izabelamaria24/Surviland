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

    SmartEnemy(const SmartEnemy& other) = default;

    [[nodiscard]] std::shared_ptr<Enemy> clone() const override { return std::make_shared<SmartEnemy>(*this); }
};
