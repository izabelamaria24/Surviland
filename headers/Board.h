
#include <vector>
#include <unordered_map>
#include <set>

#include "Player.h"
#include "Helper.h"

/*
    HEAL - 1
    ARMOR - 2
    STOPWATCH - 3
    MONEY - 4
    JACKPOT - 5
*/

enum class Category {
    HEAL, ARMOR, STOPWATCH, MONEY, JACKPOT
};

class Board {
private:
    int width;
    int height;
    std::vector<std::vector<char>>board;
    std::unordered_map<std::pair<int, int>, std::set<Category>, PairHash> marks;

public:
    Board(int width, int height) : width(width), height(height){};
    Board() = default;

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

    [[nodiscard]] bool checkValue(int x, int y, char c) const {
        return board[x][y] == c;
    }

    void check(int x, int y) {
        if (marks[{x, y}].find(Category::HEAL) != marks[{x, y}].end()) update(x, y, 'h');
        else if (marks[{x, y}].find(Category::ARMOR) != marks[{x, y}].end()) update(x, y, 'a');
        else if (marks[{x, y}].find(Category::STOPWATCH) != marks[{x, y}].end()) update(x, y, 'f');
        else if (marks[{x, y}].find(Category::MONEY) != marks[{x, y}].end()) update(x, y, '$');
        else if (marks[{x, y}].find(Category::JACKPOT) != marks[{x, y}].end()) update(x, y, 'm');
//        else update(x, y, '.');
    }

    void markPowerUps() {
        // !! posibil bug
        for (int i = 1; i <= height; i++)
            for (int j = 1; j <= width; j++)
                check(i, j);
    }
};