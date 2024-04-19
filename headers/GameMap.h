#pragma once

#include <memory>

class GameMap {
  private:
    int mapWidth;
    int mapHeight;

    std::vector<std::vector<std::shared_ptr<Block>> gameBoard;
  
  
  public:
    
    void initBoard();

  friend class MapBuilder;  
}

class MapBuilder {
  private:
    GameMap m_map;

  public:
    MapBuilder() = default;

    MapBuilder& setWidth(int width) {
      m_map.mapWidth = width;
      return *this;
    }
  
    MapBuilder& setHeight(int height) {
      m_map.mapHeight = height;
      return *this;
    }

    GameMap build() {
      return m_map;
    }
}
