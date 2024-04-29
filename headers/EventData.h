#pragma once
#include <string>

struct EventData {
    std::string name;
    char dir{};
    int x{}, y{};
    std::string type{};
    int hp{}, dmg{};
};