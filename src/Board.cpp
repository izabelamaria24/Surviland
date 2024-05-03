#include "../headers/Board.h"

int Board::getHeight() const {
    return height;
}

int Board::getWidth() const {
    return width;
}

void Board::update(int x, int y, char c) {
    board[x][y] = c;
}

char Board::getPlayer(const Player &player) const {
    return board[player.getX()][player.getY()];
}

bool Board::noMarks(int x, int y) {
    return !marks[{x, y}].money && !marks[{x, y}].heal && !marks[{x, y}].armor && !marks[{x, y}].stopwatch && !marks[{x, y}].jackpot;
}

bool Board::checkMoney(int x, int y) {
    return marks[{x, y}].money > 0;
}

bool Board::checkArmor(int x, int y) {
    return marks[{x, y}].armor > 0;
}

bool Board::checkJackpot(int x, int y) {
    return marks[{x, y}].jackpot > 0;
}

bool Board::checkHP(int x, int y) {
    return marks[{x, y}].heal > 0;
}

bool Board::checkStopwatch(int x, int y) {
    return marks[{x, y}].stopwatch > 0;
}

bool Board::checkValue(int x, int y, char c) const {
    return board[x][y] == c;
}

void Board::checkAndUpdate(int x, int y) {
    if (marks[{x, y}].heal) update(x, y, 'h');
    else if (marks[{x, y}].armor) update(x, y, 'a');
    else if (marks[{x, y}].stopwatch) update(x, y, 'f');
    else if (marks[{x, y}].money) update(x, y, '$');
    else if (marks[{x, y}].jackpot) update(x, y, 'm');
}

void Board::collect(int x, int y, char attribute, Player &player) {
    if (attribute == 'h') {
        player.collectHp(2);
        marks[{x, y}].heal = 0;
    }
    if (attribute == 'a') {
        player.collectArmor(1);
        marks[{x, y}].armor = 0;
    }
    if (attribute == 'f') marks[{x, y}].stopwatch = 0;
    if (attribute == 'm') marks[{x, y}].jackpot = 0;
    if (attribute == '$') {
        player.collectMoney(marks[{x, y}].money);
        marks[{x, y}].money = 0;
    }
}

void Board::increase(int x, int y, char attribute, int amount) {
    if (attribute == 'h') marks[{x, y}].heal += amount;
    if (attribute == 'a') marks[{x, y}].armor += amount;
    if (attribute == 'f') marks[{x, y}].stopwatch += amount;
    if (attribute == 'm') marks[{x, y}].jackpot += amount;
    if (attribute == '$') marks[{x, y}].money += amount;
}

bool Board::powerUpExist(int x, int y) {
    return board[x][y] != 'H' && board[x][y] != 'A' && board[x][y] != 'M' && board[x][y] != 'F'
           && board[x][y] != 'h' && board[x][y] != 'a' && board[x][y] != 'm' && board[x][y] != 'f';
}