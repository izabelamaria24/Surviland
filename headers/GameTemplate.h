#pragma once

#include <memory>

template <typename T>
class GameTemplate {
  private:
    static std::shared_ptr<T> gameInstance;

  public:
    GameTemplate operator=(const GameTemplate&) = delete;
    GameTemplate (const GameTemplate&) = delete; 

    static std::shared_ptr<T> getGameInstance() {
      if (!gameInstance) {
        gameInstance = std::shared_ptr<T>(new T);
      }
      
      return gameInstance;
    };

  protected:
    GameTemplate() = default;
    
    virtual ~GameTemplate() = default;
}

template <typename T>
std::shared_ptr<T> GameTemplate<T>::gameInstance = nullptr;
