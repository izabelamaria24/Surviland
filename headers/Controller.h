#pragma once

#include <string>

class Game;
struct EventData;

class Observer {
protected:
    Game& game;
public:
    explicit Observer(Game& game) : game(game){}

    virtual void update(const EventData& eventData, const std::string& type) = 0;

    virtual ~Observer() = default;
};

class PlayerController : public Observer {
private:
    void spellAttack();

    void attack();

    void move(const EventData& eventData);

    void upgrade(const EventData& eventData);

public:
    explicit PlayerController(Game& game) : Observer(game){}

    void update(const EventData& eventData, const std::string& type) override;
};

class EnemyController : public Observer {
private:
    void spawnDumbEnemy(const EventData& eventData);

    void spawnSmartEnemy(const EventData& eventData);

    void spawnDumbEnemyHoard(const EventData& eventData);

    void spawnSmartEnemyHoard(const EventData& eventData);

    void spawnObstacle(const EventData& eventData);

public:
    explicit EnemyController(Game& game) : Observer(game){}

    void update(const EventData& eventData, const std::string& type) override;
};

class PowerUpController : public Observer {
private:
    void spawnPowerup(const EventData& eventData);

public:
    explicit PowerUpController(Game& game) : Observer(game){}

    void update(const EventData& eventData, const std::string& type) override;
};