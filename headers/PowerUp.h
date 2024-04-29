#pragma once

#include "Entity.h"

class PowerUp : public Entity{
private:
    std::string type;
    bool picked;
public:
    PowerUp() : Entity(), picked(false){}

    [[nodiscard]] std::string getType() const {
        return type;
    }

//    int attack(char symbol) {
//        if (symbol == 'L') {
//            hp-=ability;
//            if (unlockedSpell) hp -= spellFeature1;
//        }
//        else hp -= spellFeature1;
//    }

    [[nodiscard]] bool dead() const {
        return hp <= 0;
    }
};