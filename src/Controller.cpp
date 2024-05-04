#include "../headers/Controller.h"
#include "../headers/Game.h"
#include "../headers/DumbEnemy.h"
#include "../headers/SmartEnemy.h"

void PlayerController::spellAttack() {
    int x = game.getPlayer().getX(), y = game.getPlayer().getY();
    int spell2 = game.getPlayer().getSpell2();

    int rangeL = y - spell2, rangeR = y + spell2;
    int lineUp = x - 1, lineDown = x + 1;

    for (int i = rangeL; i <= rangeR; i++)
        if (game.borders(x, i)) {
            bool enemyFound = false, stillAlive = false;
            game.attackEnemies(x, i, 'O', enemyFound, stillAlive);
            game.takePowerups(x, i, 'O');
        }

    rangeL++, rangeR--;

    for (int i = 1; i <= spell2; i++) {
        for (int j = rangeL; j <= rangeR; j++) {
            if (game.borders(lineUp, j)) {
                bool enemyFound = false, stillAlive = false;
                game.attackEnemies(lineUp, j, 'O', enemyFound, stillAlive);
                game.takePowerups(lineUp, j, 'O');
            }

            if (game.borders(lineDown, j)) {
                bool enemyFound = false, stillAlive = false;
                game.attackEnemies(lineDown, j, 'O', enemyFound, stillAlive);
                game.takePowerups(lineDown, j, 'O');
            }
        }
        lineUp--, lineDown++, rangeL++, rangeR--;
    }
}

void PlayerController::attack() {
    int addX = game.checkPlayerDirection().first, addY = game.checkPlayerDirection().second;
    int newX = game.getPlayer().getX(), newY = game.getPlayer().getY();
    int abilityRange = game.getPlayer().getRange();
    bool unlockedSpell = game.getPlayer().availableSpell();

    for (int i = 1; i <= abilityRange; i++) {
        newX += addX;
        newY += addY;
        if (game.borders(newX, newY)) {
            bool enemyFound = false, stillAlive = false;
            game.attackEnemies(newX, newY, 'L', enemyFound, stillAlive);
            game.takePowerups(newX, newY, 'L');
        }
    }

    if (unlockedSpell) spellAttack();
    game.moveEnemies();

    newX = game.getPlayer().getX(), newY = game.getPlayer().getY();

    for (int i = 1; i <= abilityRange; i++) {
        newX += addX;
        newY += addY;

        if (game.borders(newX, newY)) {
            bool enemyFound = false, stillAlive = false;

            game.attackEnemies(newX, newY, 'L', enemyFound, stillAlive);

            if (!enemyFound || !stillAlive)
                if (game.getBoard().powerUpExist(newX, newY))
                    game.getBoard().update(newX, newY, 'L');
        }
    }

    if (unlockedSpell) {
        spellAttack();
        game.drawSpell();
    }

    game.markEntities();
    game.healEnemies();
}

void PlayerController::move(const EventData& eventData) {
        char dir = eventData.dir;

        game.clearAttack();
        game.healEnemies();

        int x = game.getPlayer().getX(), y = game.getPlayer().getY();

        if (dir == 'L') {
            if (!game.checkCollision(x, y - 1)) {
                game.getBoard().update(x, y, '.');
                if (y > 1) game.getPlayer().move(x, y - 1);
            }

            game.collectResources();
            x = game.getPlayer().getX(), y = game.getPlayer().getY();
            game.getBoard().update(x, y, '<');
        }

        if (dir == 'R') {
            if (!game.checkCollision(x, y + 1)) {
                game.getBoard().update(x, y, '.');
                if (y < game.getBoard().getWidth()) game.getPlayer().move(x, y + 1);
            }

            game.collectResources();
            x = game.getPlayer().getX(), y = game.getPlayer().getY();
            game.getBoard().update(x, y, '>');
        }

        if (dir == 'D') {
            if (!game.checkCollision(x + 1, y)) {
                game.getBoard().update(x, y, '.');
                if (x < game.getBoard().getHeight()) game.getPlayer().move(x + 1, y);
            }

            game.collectResources();
            x = game.getPlayer().getX(), y = game.getPlayer().getY();
            game.getBoard().update(x, y, 'v');
        }

        if (dir == 'U') {
            if (!game.checkCollision(x - 1, y)) {
                game.getBoard().update(x, y, '.');
                if (x > 1) game.getPlayer().move(x - 1, y);
            }
            game.collectResources();
            x = game.getPlayer().getX(), y = game.getPlayer().getY();
            game.getBoard().update(x, y, '^');
        }

        game.checkPortal();

        game.changeEnemiesDirection();
        game.moveEnemies();
        game.markEntities();
}

void PlayerController::upgrade(const EventData& eventData) {
    if (eventData.type == "L") {
        if (!game.getPlayer().verifyAvailableUpgrades())
            game.updateOutputMessage("Not enough Ability Points! Go and slay more monsters!");
        else {
            game.getPlayer().upgradeNormalAttack();
            game.updateOutputMessage("Your ability grew stronger!");
        }
    }

    if (eventData.type == "O") {
        if (!game.getPlayer().verifyAvailableUpgrades())
            game.updateOutputMessage("Not enough Ability Points! Go and slay more monsters!");
        else {
            if (!game.getPlayer().availableSpell())
                game.updateOutputMessage("You learnt a new spell!");
            else {
                game.updateOutputMessage("Your ability grew stronger!");
                game.getPlayer().upgradeSpellAttack();
            }

            game.getPlayer().unlockSpell();
            game.getPlayer().substractUpgrade();
        }
    }
}

void PlayerController::update(const EventData& eventData) {
    if (eventData.name == "ATT")
        attack();
    if (eventData.name == "M")
        move(eventData);
    if (eventData.name == "UP")
        upgrade(eventData);
}

void EnemyController::spawnDumbEnemy(const EventData &eventData) {
    std::shared_ptr<Enemy> newEnemy = std::make_shared<DumbEnemy>(eventData.x, eventData.y, eventData.dmg,
                                                                   eventData.hp, eventData.dir);
    game.addEnemy(newEnemy);
    game.markEntities();
}

void EnemyController::spawnSmartEnemy(const EventData &eventData) {
    std::shared_ptr<Enemy> newEnemy = std::make_shared<SmartEnemy>(eventData.x, eventData.y, eventData.dmg,
                                                                    eventData.hp, game.getBoard().getPlayer(game.getPlayer()));
    game.addEnemy(newEnemy);
    game.markEntities();
}

void EnemyController::spawnDumbEnemyHoard(const EventData& eventData) {
    int xSwf = eventData.x, ySwf = eventData.y;

    std::shared_ptr<Enemy> newEnemy1 = std::make_shared<DumbEnemy>(xSwf, ySwf, eventData.dmg, eventData.hp, eventData.dir);
    std::shared_ptr<Enemy> newEnemy2 = newEnemy1->clone();
    newEnemy2->moveOneStep(xSwf, ySwf + 1);
    std::shared_ptr<Enemy> newEnemy3 = newEnemy1->clone();
    newEnemy3->moveOneStep(xSwf, ySwf + 2);

    game.addEnemy(newEnemy1);
    game.addEnemy(newEnemy2);
    game.addEnemy(newEnemy3);

    game.clearAttack();
    game.markEntities();
}

void EnemyController::spawnSmartEnemyHoard(const EventData &eventData) {
    int height = game.getBoard().getHeight();
    int width = game.getBoard().getWidth();

    const int coordX[] = {1, 1, height, height};
    const int coordY[] = {width, 1, width, 1};

    std::shared_ptr<Enemy> newEnemy0 = std::make_shared<SmartEnemy>(coordX[0], coordY[0], eventData.hp, eventData.dmg,
                                                                    game.getBoard().getPlayer(game.getPlayer()));
    game.addEnemy(newEnemy0);

    for (int coord = 1; coord < 4; coord++) {
        std::shared_ptr<Enemy> newEnemy = newEnemy0->clone();
        newEnemy->moveOneStep(coordX[coord], coordY[coord]);
    }

    game.clearAttack();
    game.markEntities();
}

void EnemyController::update(const EventData &eventData) {
    if (eventData.name == "SF") {
        spawnDumbEnemy(eventData);
    }

    if (eventData.name == "ST") {
        spawnSmartEnemy(eventData);
    }

    if (eventData.name == "SWF") {
        spawnDumbEnemyHoard(eventData);
    }

    if (eventData.name == "SWT") {
        spawnSmartEnemyHoard(eventData);
    }
}

void PowerUpController::spawnPowerup(const EventData &eventData) {
    game.addPowerup(eventData.x, eventData.y, eventData.hp, eventData.type);
    game.clearAttack();
    game.markEntities();
}

void PowerUpController::update(const EventData& eventData) {
    spawnPowerup(eventData);
}

