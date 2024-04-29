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
    int abilityRange;
    bool unlockedSpell;

public:
    Player(int x, int y, int hp, int armor) : Entity(x, y, hp), level(1), armor(armor), totalMoney(0), spellFeature1(1), spellFeature2(1), ability(1), abilityRange(1), unlockedSpell(false){};
    Player() : Entity(-1, -1, -1), level(-1), armor(-1), totalMoney(-1), timeLeft(-1), spellFeature1(-1), spellFeature2(-1), ability(-1), abilityRange(-1), unlockedSpell(false){};

    void levelUp() {
        level++;
    }

    void collectMoney(int amount) {
        totalMoney += amount;
    }

    void collectHp(int amount) {
        hp += amount;
        hp = std::min(10, hp);
    }

    void collectArmor(int amount) {
        armor += amount;
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

    void resetStopwatch() {
        timeLeft = 4;
    }

    [[nodiscard]] int getRange() const {
        return abilityRange;
    }
};

