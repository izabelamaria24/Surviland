
#include <vector>

#include "Entity.h"

class Board {
private:
    int width{};
    int height{};
    std::vector<std::vector<Entity>>board;
public:
    Board(int width, int height) : width(width), height(height){};
    Board() = default;

    [[nodiscard]] int getHeight() const {
        return height;
    }

    [[nodiscard]] int getWidth() const {
        return width;
    }
};