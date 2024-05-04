#pragma once

#include "Entity.h"
#include <algorithm>

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
    int availableAbilityUpgrades;
    int upgrade;
    int spellUpgrade;

public:
    Player() : Entity(-1, -1, -1), level(-1), armor(-1), totalMoney(-1), timeLeft(-1), spellFeature1(-1), spellFeature2(-1),
               ability(-1), abilityRange(-1), unlockedSpell(false), availableAbilityUpgrades(-1), upgrade(-1), spellUpgrade(0) {};
    Player(int x, int y, int hp, int armor) : Entity(x, y, hp), level(1), armor(armor), totalMoney(0), spellFeature1(1), spellFeature2(1),
                    ability(1), abilityRange(1), unlockedSpell(false), availableAbilityUpgrades(0), upgrade(0), spellUpgrade(0) {};

    void move(int x1, int y1);

    void levelUp();

    [[nodiscard]] int getLevel() const;
    [[nodiscard]] int getMoney() const;

    void upgradeNormalAttack();
    void upgradeSpellAttack();

    void unlockSpell();

    [[nodiscard]] bool verifyAvailableUpgrades() const;

    void substractUpgrade();

    void collectMoney(int amount);
    void collectHp(int amount);
    void collectArmor(int amount);

    [[nodiscard]] bool updateAvailable() const;

    void payUpgrade();

    bool isDead();

    [[nodiscard]] bool checkTime() const;

    void decreaseHp(int attack);

    [[nodiscard]] int getSpell1() const;
    [[nodiscard]] int getSpell2() const;
    [[nodiscard]] int getAbility() const;
    [[nodiscard]] int getHP() const;
    [[nodiscard]] int getArmor() const;

    [[nodiscard]] bool availableSpell() const;

    void resetStopwatch();

    void decreaseTime();

    [[nodiscard]] int getRange() const;

    void increaseAvailableUpgrades();

    Player(const Player& other) = default;

    Player& operator=(Player other) noexcept {
        swap(*this, other);
        return *this;
    }

    friend void swap(Player& p1, Player& p2) {
        using std::swap;
        swap(static_cast<Entity&>(p1), static_cast<Entity&>(p2));
        swap(p1.level, p2.level);
        swap(p1.armor, p2.armor);
        swap(p1.totalMoney, p2.totalMoney);
        swap(p1.spellFeature1, p2.spellFeature1);
        swap(p1.spellFeature2, p2.spellFeature2);
        swap(p1.ability, p2.ability);
        swap(p1.abilityRange, p2.abilityRange);
        swap(p1.unlockedSpell, p2.unlockedSpell);
        swap(p1.availableAbilityUpgrades, p2.availableAbilityUpgrades);
        swap(p1.upgrade, p2.upgrade);
        swap(p1.spellUpgrade, p2.spellUpgrade);
    }
};

