
#include <vector>
#include <unordered_map>
#include <set>

#include "Player.h"
#include "Helper.h"
#include <iostream>

struct Category {
    int heal;
    int armor;
    int jackpot;
    int money;
    int stopwatch;
};

class Board {
private:
    int width{};
    int height{};
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

    [[nodiscard]] int getHeight() const;
    [[nodiscard]] int getWidth() const;

    void update(int x, int y, char c);

    char getPlayer(const Player& player) const;

    bool noMarks(int x, int y);
    bool checkMoney(int x, int y);
    bool checkArmor(int x, int y);
    bool checkJackpot(int x, int y);
    bool checkHP(int x, int y);
    bool checkStopwatch(int x, int y);
    [[nodiscard]] bool checkValue(int x, int y, char c) const;
    void checkAndUpdate(int x, int y);

    void collect(int x, int y, char attribute, Player& player);

    void increase(int x, int y, char attribute, int amount);

    bool powerUpExist(int x, int y);
};