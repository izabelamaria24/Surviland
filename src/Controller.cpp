#include "../headers/Controller.h"
#include "../headers/Game.h"

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

void PlayerController::attack(EventData& eventData) {
    int addX = game.checkPlayerDirection().first, addY = game.checkPlayerDirection().second;
    int newX = game.getPlayer().getX(), newY = game.getPlayer().getY();
    int abilityRange = game.getPlayer().getRange();
    bool unlockedSpell = game.getPlayer().availableSpell();

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

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

            if (!enemyFound || (enemyFound && !stillAlive))
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

void PlayerController::move(EventData& eventData) {
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

        game.changeEnemiesDirection();
        game.moveEnemies();
        game.markEntities();
}

void PlayerController::upgrade(EventData& eventData) {
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

void PlayerController::update(EventData& eventData) {
    if (eventData.name == "ATT")
        attack(eventData);
    if (eventData.name == "M")
        move(eventData);
    if (eventData.name == "UP")
        upgrade(eventData);
}

void EnemyController::spawnDumbEnemy(EventData &eventData) {
    game.moveEnemies();
    game.addEnemy(eventData.x + 1, eventData.y + 1, eventData.dmg, eventData.hp, eventData.dir, 1);
    game.markEntities();
}

void EnemyController::spawnSmartEnemy(EventData &eventData) {
    game.moveEnemies();
    game.addEnemy(eventData.x + 1, eventData.y + 1, eventData.dmg, eventData.hp, game.getBoard().getPlayer(game.getPlayer()), 2);
    game.markEntities();
}

void EnemyController::spawnDumbEnemyHoard(EventData& eventData) {
    game.moveEnemies();
    int xSwf = eventData.x, ySwf = eventData.y;
    for (int i = 1; i <= 3; i++) {
        game.addEnemy(xSwf + 1, ySwf + 1, eventData.dmg, eventData.hp, eventData.dir, 1);
        ySwf++;
    }
    game.clearAttack();
    game.markEntities();
}

void EnemyController::spawnSmartEnemyHoard(EventData &eventData) {
    game.moveEnemies();

    int height = game.getBoard().getHeight();
    int width = game.getBoard().getWidth();

    const int coordX[] = {1, 1, height, height};
    const int coordY[] = {width, 1, width, 1};

    for (int coord = 0; coord < 4; coord++)
        game.addEnemy(coordX[coord], coordY[coord], eventData.dmg, eventData.hp, game.getBoard().getPlayer(game.getPlayer()), 2);

    game.clearAttack();
    game.markEntities();
}

void EnemyController::update(EventData &eventData) {
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

void PowerUpController::spawnPowerup(EventData &eventData) {
    game.moveEnemies();
    game.addPowerup(eventData.x + 1, eventData.y + 1, eventData.hp, eventData.type);
    game.clearAttack();
    game.markEntities();
}

void PowerUpController::update(EventData& eventData) {
    spawnPowerup(eventData);
}

