#pragma once
#include <memory>
#include "Exceptions.h"

class Entity {
protected:
    int x;
    int y;
    int hp;
public:
    Entity() : x(0), y(0), hp(10){};
    Entity(int x, int y) : x(x), y(y){};
    Entity(int x, int y, int hp) : x(x), y(y), hp(hp){};

    [[nodiscard]] int getX() const {
        return x;
    }

    [[nodiscard]] int getY() const {
        return y;
    }

    Entity(const Entity& other) = default;

    virtual ~Entity() = default;
};