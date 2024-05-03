#pragma once
#include <memory>

class Entity {
protected:
    int x;
    int y;
    int hp;
public:
    Entity() : x(0), y(0), hp(10){};
    Entity(int x, int y, int hp) : x(x), y(y), hp(hp){};

    [[nodiscard]] int getX() const {
        return x;
    }

    [[nodiscard]] int getY() const {
        return y;
    }

//    Entity& operator=(Entity other) {
//        swap(*this, other);
//        return *this;
//    }
//
//    friend void swap(Entity& e1, Entity& e2) {
//        using std::swap;
//        swap(e1.x, e2.x);
//        swap(e1.y, e2.y);
//        swap(e1.hp, e2.hp);
//    }

    virtual ~Entity() = default;
};