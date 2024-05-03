#pragma once

#include <utility>

#include "Entity.h"

class PowerUp : public Entity{
private:
    const std::string type;
    bool lastHit;
public:
    PowerUp() : Entity(), lastHit(false){}
    PowerUp(int x, int y, int hp, std::string  type) : Entity(x, y, hp), type(std::move(type)), lastHit(false){};

    [[nodiscard]] std::string getType() const {
        return type;
    }

    void attack(char symbol, int att1, int att2, bool spell) {
        if (symbol == 'L') {
            hp-=att1; // ability
            if (spell) hp -= att2; // spellFeature1
        }
        else hp -= att2;
    }

    void activateHit() {
        lastHit = true;
    }

//    void undoHit() {
//        lastHit = false;
//    }

    [[nodiscard]] bool checkLastHit() const {
        return lastHit;
    }

    [[nodiscard]] bool dead() const {
        return hp <= 0;
    }
};