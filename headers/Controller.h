#pragma once

#include <string>

class Game;
struct EventData;

class Observer {
protected:
    Game& game;
public:
    explicit Observer(Game& game) : game(game){}

    virtual void update(EventData& eventData) = 0;

    virtual ~Observer() = default;
};

class PlayerController : public Observer {
private:
    void spellAttack();

    void attack();

    void move(EventData& eventData);

    void upgrade(EventData& eventData);

public:
    explicit PlayerController(Game& game) : Observer(game){}

    void update(EventData& eventData) override;
};

class EnemyController : public Observer {
private:
    void spawnDumbEnemy(EventData& eventData);

    void spawnSmartEnemy(EventData& eventData);

    void spawnDumbEnemyHoard(EventData& eventData);

    void spawnSmartEnemyHoard(EventData& eventData);

public:
    explicit EnemyController(Game& game) : Observer(game){}

    void update(EventData& eventData) override;
};

class PowerUpController : public Observer {
private:
    void spawnPowerup(EventData& eventData);

public:
    explicit PowerUpController(Game& game) : Observer(game){}

    void update(EventData& eventData) override;
};