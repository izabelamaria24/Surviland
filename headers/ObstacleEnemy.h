#pragma once

#include "Enemy.h"

class ObstacleEnemy : public Enemy {
public:
    ObstacleEnemy(int x, int y) : Enemy(x, y){

    }

    void changeDirection(Board& board, Player& player) override;
    void goBack(Board& board, Player& player) override;

    [[nodiscard]] std::shared_ptr<Enemy> clone() const override {
        return std::make_shared<ObstacleEnemy>(*this);
    }
};