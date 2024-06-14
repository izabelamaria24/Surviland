#include "../headers/DumbEnemy.h"

void DumbEnemy::changeDirection(Board &board, Player &player) {
    if (dir == 'U' && x > 0 && player.getX()) x--;
    if (dir == 'D' && x <= board.getHeight()) x++;
    if (dir == 'L' && y > 0) y--;
    if (dir == 'R' && y <= board.getWidth()) y++;
}

void DumbEnemy::goBack(Board &board, Player &player) {
    if (dir == 'U' && x <= board.getHeight() && player.getX()) x++;
    if (dir == 'D' && x > 0) x--;
    if (dir == 'L' && y <= board.getWidth()) y++;
    if (dir == 'R' && y > 0) y--;
}