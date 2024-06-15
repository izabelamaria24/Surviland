#pragma once

#include <vector>
#include <fstream>
#include <string>

#include "Exceptions.h"
#include "GameData.h"

class Parser {
public:
    std::vector<GameData> loadGameData(const std::string& filename);
    void saveGameData(const std::vector<GameData>&dataList, const std::string& filename);
    void addGameData(const GameData& newData, const std::string&filename);
};