#include "../headers/Parser.h"

std::vector<GameData> Parser::loadGameData(const std::string &filename) {
    std::vector<GameData> dataList;

    if (!std::filesystem::exists(filename) || std::filesystem::is_empty(filename)) {
        std::ofstream file(filename);
        file << "[]";
        file.close();
        return dataList;
    }

    std::ifstream file(filename);

    if (!file.is_open())
        throw LogicError("Failed to open JSON file for reading.");

    nlohmann::json jsonData;
    file >> jsonData;
    file.close();

    if (jsonData.is_array()) {
        for (const auto& dataItem : jsonData) {
            GameData data;
            dataItem.get_to(data);
            dataList.push_back(data);
        }
    } else {
        throw LogicError("Invalid JSON format: expected an array");
    }

    return dataList;
}

void Parser::saveGameData(const std::vector<GameData> &dataList, const std::string &filename) {
    nlohmann::json jsonData = dataList;

    std::ofstream file(filename);
    if (file.is_open()) {
        file << jsonData.dump(4);
        file.close();
    } else {
        throw LogicError("Failed to open JSON file for writing.");
    }
}

void Parser::addGameData(const GameData &newData, const std::string &filename) {
    std::vector<GameData> gameDataList = loadGameData(filename);
    gameDataList.push_back(newData);
    saveGameData(gameDataList, filename);
}