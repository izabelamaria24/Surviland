#pragma once

#include "Entity.h"

class Portal : public Entity{
private:
    int xdest;
    int ydest;
public:
    Portal(int x, int y, int xdest, int ydest, int hp) : Entity(x, y, hp), xdest(xdest), ydest(ydest){}

    // for the portal, hp equal to the number of times it can be used
    void use();

    bool destroyed();

    [[nodiscard]] int getX2() const;

    [[nodiscard]] int getY2() const;

    Portal(const Portal& other) = default;
};