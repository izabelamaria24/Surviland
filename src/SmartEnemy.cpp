#include "../headers/SmartEnemy.h"

void SmartEnemy::track(const Player &player) {
    prevX = x;
    prevY = y;

    int playerX = player.getX();
    int playerY = player.getY();

    if (x > playerX) x--;
    else if (x < playerX) x++;
    else {
        if (y > playerY) y--;
        else y++;
    }
}

void SmartEnemy::changeDirection(Board &board, Player &player) {
    (void)board;
    track(player);
}

void SmartEnemy::goBack(Board &board, Player &player) {
    (void)board;
    (void)player;
    x = prevX;
    y = prevY;
}