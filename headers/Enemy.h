#pragma once

#include "Entity.h"

class Enemy : public Entity{
    int dmg;
    char dir;
    bool hit;

public:
};

class DumbEnemy : public Enemy{
    
};

class SmartEnemy : public Enemy{

};