#include "../headers/Player.h"

void Player::move(int x1, int y1) {
    x = x1;
    y = y1;
}

void Player::levelUp() {
    level++;
    if (spellUpgrade) spellUpgrade++; // TODO: USE SPELL UPGRADE (THIS IS FOR WARNING SOLVING)
}

int Player::getLevel() const {
    return level;
}

int Player::getMoney() const {
    return totalMoney;
}

void Player::upgradeNormalAttack() {
    ability *= 2;
    abilityRange++;
    upgrade++;
    availableAbilityUpgrades--;
}

void Player::upgradeSpellAttack() {
    spellFeature1 *= 2;
    spellFeature2++;
    spellUpgrade++;
}

void Player::unlockSpell() {
    unlockedSpell = true;
}

bool Player::verifyAvailableUpgrades() const {
    return availableAbilityUpgrades >= 1;
}

void Player::substractUpgrade() {
    availableAbilityUpgrades--;
}

void Player::collectMoney(int amount) {
    totalMoney += amount;
}

void Player::collectHp(int amount) {
    hp += amount;
    hp = std::min(10, hp);
}

void Player::collectArmor(int amount) {
    armor += amount;
}

bool Player::updateAvailable() const {
    return totalMoney >= 10;
}

void Player::payUpgrade() {
    totalMoney -= 10;
}

bool Player::isDead() {
    return hp <= 0;
}

bool Player::checkTime() const {
    return timeLeft > 0;
}

void Player::decreaseHp(int attack) {
    hp -= std::max(0, attack - armor);
}

int Player::getSpell1() const {
    return spellFeature1;
}

int Player::getSpell2() const {
    return spellFeature2;
}

int Player::getAbility() const {
    return ability;
}

int Player::getHP() const {
    return hp;
}

int Player::getArmor() const {
    return armor;
}

bool Player::availableSpell() const {
    return unlockedSpell;
}

void Player::resetStopwatch() {
    timeLeft = 4;
}

void Player::decreaseTime() {
    if (timeLeft > 0)
        timeLeft--;
}

int Player::getRange() const {
    return abilityRange;
}

void Player::increaseAvailableUpgrades() {
    availableAbilityUpgrades++;
}