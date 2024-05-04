#pragma once

#include <utility>

#include "Entity.h"

class PowerUp : public Entity{
private:
    std::string type;
    bool lastHit;
public:
    PowerUp() : Entity(), lastHit(false){}
    PowerUp(int x, int y, int hp, std::string  type) : Entity(x, y, hp), type(std::move(type)), lastHit(false){};

    [[nodiscard]] std::string getType() const {
        return type;
    }

    void attack(char symbol, int att1, int att2, bool spell) {
        if (symbol == 'L') {
            hp -= att1;
            if (spell) hp -= att2;
        }
        else hp -= att2;
    }

    void activateHit() {
        lastHit = true;
    }

    [[nodiscard]] bool checkLastHit() const {
        return lastHit;
    }

    [[nodiscard]] bool dead() const {
        return hp <= 0;
    }

    PowerUp(const PowerUp& other) = default;

    PowerUp& operator=(PowerUp&& other) noexcept {
        swap(*this, other);
        return *this;
    }

    friend void swap(PowerUp& p1, PowerUp& p2) {
        using std::swap;
        swap(static_cast<Entity&>(p1), static_cast<Entity&>(p2));
        swap(p1.type, p2.type);
        swap(p1.lastHit, p2.lastHit);
    }
};