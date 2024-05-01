
#include <vector>
#include <unordered_map>
#include <set>

#include "Player.h"
#include "Helper.h"
#include <iostream>
/*
    HEAL - 1
    ARMOR - 2
    STOPWATCH - 3
    MONEY - 4
    JACKPOT - 5
*/

struct Category {
    int heal;
    int armor;
    int jackpot;
    int money;
    int stopwatch;
};

class Board {
private:
    int width;
    int height;
    std::vector<std::vector<char>>board;
    std::unordered_map<std::pair<int, int>, Category, PairHash> marks;

public:
    Board(int width, int height) : width(width), height(height), board(height + 2, std::vector<char>(width + 2)){
        for (int i = 0; i < height + 2; ++i) {
            for (int j = 0; j < width + 2; ++j) {
                board[i][j] = '.';
            }
        }
    };
    Board() = default;

    void displayBoard() const {
        for (int i = 1; i <= height; i++, std::cout << '\n')
            for (int j = 1; j <= width; j++)
                std::cout << board[i][j];
    }

    [[nodiscard]] int getHeight() const {
        return height;
    }

    [[nodiscard]] int getWidth() const {
        return width;
    }

    void update(int x, int y, char c) {
        board[x][y] = c;
    }

    char getPlayer(Player& player) const {
        return board[player.getX()][player.getY()];
    }

    bool checkMoney(int x, int y) {
        return marks[{x, y}].money > 0;
    }

    bool checkArmor(int x, int y) {
        return marks[{x, y}].armor > 0;
    }

    bool checkJackpot(int x, int y) {
        return marks[{x, y}].jackpot > 0;
    }

    bool checkHP(int x, int y) {
        return marks[{x, y}].heal > 0;
    }

    bool checkStopwatch(int x, int y) {
        return marks[{x, y}].stopwatch > 0;
    }

    [[nodiscard]] bool checkValue(int x, int y, char c) const {
        return board[x][y] == c;
    }

    void checkAndUpdate(int x, int y) {
        if (marks[{x, y}].heal) update(x, y, 'h');
        else if (marks[{x, y}].armor) update(x, y, 'a');
        else if (marks[{x, y}].stopwatch) update(x, y, 'f');
        else if (marks[{x, y}].money) update(x, y, '$');
        else if (marks[{x, y}].jackpot) update(x, y, 'm');
        else update(x, y, '.');
         // TODO LAST CONDITION MAY CAUSE BUGS
    }

    void collect(int x, int y, char attribute, Player& player) {
        if (attribute == 'h') {
            player.collectHp(5);
            marks[{x, y}].heal = 0;
        }
        if (attribute == 'a') {
            player.collectArmor(5);
            marks[{x, y}].armor = 0;
        }
        if (attribute == 's') marks[{x, y}].stopwatch = 0;
        if (attribute == 'm') marks[{x, y}].jackpot = 0;
        if (attribute == '$') {
            player.collectMoney(marks[{x, y}].money);
            marks[{x, y}].money = 0;
        }
    }

    void increase(int x, int y, char attribute, int amount) {
        if (attribute == 'h') marks[{x, y}].heal += amount;
        if (attribute == 'a') marks[{x, y}].armor += amount;
        if (attribute == 's') marks[{x, y}].stopwatch += amount;
        if (attribute == 'm') marks[{x, y}].jackpot += amount;
        if (attribute == '$') marks[{x, y}].money += amount;
    }


    void markPowerUps() {
        for (int i = 1; i <= height; i++)
            for (int j = 1; j <= width; j++)
                checkAndUpdate(i, j);
    }

    bool powerUpExist(int x, int y) {
        return board[x][y] != 'H' && board[x][y] != 'A' && board[x][y] != 'M' && board[x][y] != 'F'
               && board[x][y] != 'h' && board[x][y] != 'a' && board[x][y] != 'm' && board[x][y] != 'f';
    }
};