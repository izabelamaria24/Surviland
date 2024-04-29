#pragma once

#include "Entity.h"

class Player : public Entity {
private:
    int level;
    int armor;
    int totalMoney;
    int timeLeft = 0;
    int spellFeature1;
    int spellFeature2;
    int ability;
    bool unlockedSpell;

public:
    Player(int x, int y, int hp, int armor) : Entity(x, y, hp), level(1), armor(armor), totalMoney(0), spellFeature1(1), spellFeature2(1), ability(1), unlockedSpell(false) {};

    void levelUp() {
        level++;
    }

    void gainMoney(int amount) {
        totalMoney += amount;
    }

    [[nodiscard]] bool updateAvailable() const {
        return totalMoney >= 10;
    }

    void payUpgrade() {
        totalMoney -= 10;
    }

    [[nodiscard]] bool checkTime() const {
        return timeLeft > 0;
    }

    void decreaseHp(int attack) {
        hp -= std::max(0, attack - armor);
    }

    [[nodiscard]] int getSpell1() const {
        return spellFeature1;
    }

    [[nodiscard]] int getSpell2() const {
        return spellFeature2;
    }

    [[nodiscard]] int getAbility() const {
        return ability;
    }

    [[nodiscard]] bool availableSpell() const {
        return unlockedSpell;
    }
};

