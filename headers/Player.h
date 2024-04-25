#pragma once

#include "Entity.h"

class Player : public Entity {
private:
    int level;
    int armor;
    int totalMoney;
    int timeLeft = 0;

public:
    Player(int level, int armor, int totalMoney, int x, int y, int hp) : Entity(x, y, hp), level(level), armor(armor), totalMoney(totalMoney){};
    Player() = default;
};

