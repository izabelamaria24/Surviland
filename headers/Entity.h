#pragma once
#include <memory>

class Entity {
protected:
    int x;
    int y;
    int hp;
public:
    Entity() = default;
    Entity(int x, int y, int hp) : x(x), y(y), hp(hp){};

    [[nodiscard]] int getX() const {
        return x;
    }

    [[nodiscard]] int getY() const {
        return y;
    }

    friend class EntityBuilder;
};