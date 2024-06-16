#include <string>
#include "../generated/include/json.hpp"

struct GameData {
    int level;
    int ability;
    std::string date;
    bool win;

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(GameData, level, ability, date, win);
};