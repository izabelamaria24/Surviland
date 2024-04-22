#pragma once

#include "Entity.h"

class Enemy : public Entity{
    int dmg;
    char dir;
    bool hit;
};

class DumbEnemy : public Enemy{

};

class SmartEnemy : public Enemy{

};