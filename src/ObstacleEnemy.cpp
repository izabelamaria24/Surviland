#include "../headers/ObstacleEnemy.h"

void ObstacleEnemy::changeDirection(Board &board, Player &player) {
    if (!player.getX()) return;
    if (!board.getWidth()) return;
}

void ObstacleEnemy::goBack(Board &board, Player &player) {
    if (!player.getX()) return;
    if (!board.getWidth()) return;
}