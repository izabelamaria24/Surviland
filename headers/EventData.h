#pragma once
#include <string>

struct EventData {
    char dir{};
    int x{}, y{};
    std::string type{};
    int hp{}, dmg{};
};