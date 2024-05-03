#include "../headers/Enemy.h"

void Enemy::modifyDirection(char newDir) {
    dir = newDir;
}

void Enemy::activateHit() {
    lastHit = true;
}

bool Enemy::checkLastHit() const {
    return lastHit;
}

void Enemy::moveOneStep(int x1, int y1) {
    x = x1;
    y = y1;
}

void Enemy::hitEnemy(char symbol, int att1, int att2, bool spell) {
    hit = true;
    if (symbol == 'L') {
        hp-=att1; // ability
        if (spell) hp -= att2; // spellFeature1
    }
    else hp -= att2;
    if (hp <= 0) decreaseAttackDamage();
}

void Enemy::enemyRecover() {
    hit = false;
}

bool Enemy::isHit() const {
    return hit;
}

bool Enemy::isAlive() const {
    return hp > 0;
}

int Enemy::attackDamage() const {
    return dmg;
}

void Enemy::decreaseAttackDamage() {
    dmg = 0;
}