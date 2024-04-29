#include "../headers/Game.h"

void Game::clearScreen(sf::RenderWindow& window) {
    window.clear();
}

void Game::start(sf::RenderWindow& window) {
    window.setActive(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // TODO handle game events
        }

        window.clear();
        render(window);
        window.display();
    }
}

void Game::render(sf::RenderWindow &window) {
  sf::Font font;
  if (!font.loadFromFile("../fonts/Roboto-Black.ttf")) {
    // TODO throw exception
  }

    // Load the background image
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../assets/hogrider.png")) {
        // TODO throw exception
    }

    sf::Texture dumbEnemyTexture;
    if (!dumbEnemyTexture.loadFromFile("../assets/hogrider.png")) {
        // TODO throw exception
    }

    sf::Texture smartEnemyTexture;
    if (!smartEnemyTexture.loadFromFile("")) {
        // TODO throw exception
    }

    sf::Texture spellTexture;
    if (!spellTexture.loadFromFile("../assets/spell.png")) {
        // TODO throw exception
    }

  const int cellSize = 100;
    for (int i = 0; i < board.getHeight(); ++i) {
        for (int j = 0; j < board.getWidth(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(i * cellSize, j * cellSize);
            cell.setOutlineThickness(1);
            cell.setOutlineColor(sf::Color::Red);
            cell.setFillColor(sf::Color::White);

            if (player.getX() == i && player.getX() == j)
                cell.setTexture(&playerTexture);
            window.draw(cell);
        }
    }
}

bool Game::borders(int x, int y) {
    return x >= 1 && x <= board.getWidth() && y >= 1 && y <= board.getHeight();
}

void Game::update() {
    while (player.updateAvailable()) {
        player.levelUp();
//        availableAbilityUpgrades++;
        player.payUpgrade();
    }
}

bool Game::checkVictory() const {
    return time >= 100;
}

void Game::win() {
    victory = true;
    outputMessage = "VICTORY!";
    gameOver = true;
    update();
}

void Game::markEnemies() {
    for (const auto& enemy : enemies)
        if (enemy->isAlive()) {
            if (enemy->isHit()) board.update(enemy->getX(), enemy->getY(), 'x');
            else board.update(enemy->getX(), enemy->getY(), '+');
        }
}

void Game::moveEnemies() {
    if (player.checkTime()) return;

    for (auto& enemy : enemies){
        enemy->changeDirection(board, player);
        int x = enemy->getX(), y = enemy->getY();
        enemy->goBack(board, player);

        if (!(x == player.getX() && y == player.getY())) {
            board.check(enemy->getX(), enemy->getY());
            // TODO CHECK IF board[x][y] has powerup
            enemy->changeDirection(board, player);
        } else {
            if (enemy->isAlive() && !board.checkValue(enemy->getX(), enemy->getY(), 'L')) {
                player.decreaseHp(enemy->attackDamage());
            }
        }
    }
}

bool Game::checkCollision(int x, int y) const {
    for (const auto &enemy : enemies) {
        if (enemy->getX() == x && enemy->getY() == y) {
            return true;
        }
    }
    for (const auto &powerup : powerUps) {
        if (powerup.getX() == x && powerup.getY() == y) {
            return true;
        }
    }

    return false;
}

void Game::clearSpell() {
    char playerInitialState = board.getPlayer(player);

    int rangeL = player.getY() - player.getSpell2(), rangeR = player.getY() + player.getSpell2();
    int lineUp = player.getX() - 1, lineDown = player.getX() + 1;

    for (int i = rangeL; i <= rangeR; i++)
        if (borders(player.getX(), i)) board.update(player.getX(), i, '.');

    rangeL++, rangeR--;

    for (int i = 1; i <= player.getSpell2(); i++) {
        for (int j = rangeL; j <= rangeR; j++) {
            if (borders(lineUp, j)) board.update(lineUp, j, '.');

            if (borders(lineDown, j)) board.update(lineDown, j, '.');
        }
        lineUp--, lineDown++, rangeL++, rangeR--;
    }
    board.update(player.getX(), player.getY(), playerInitialState);
}

void Game::clearAttack() {
    int addX = checkPlayerDirection().first, addY = checkPlayerDirection().second;
    int newX = player.getX(), newY = player.getY();

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (int i = 1; i <= player.getAbility(); i++) {
        newX += addX;
        newY += addY;

        if (borders(newX, newY))
            if (board.checkValue(newX, newY, 'L')) board.update(newX, newY, '.');
    }

    if (player.availableSpell()) clearSpell();

    for (int i = 1; i <= board.getHeight(); i++)
        for (int j = 1; j <= board.getHeight(); j++)
            board.check(i, j);
}

std::pair<int, int> Game::checkPlayerDirection() {
    char ch = board.getPlayer(player);
    switch (ch) {
        case '^':
            return {-1, 0};
        case '<':
            return {0, -1};
        case '>':
            return {0, 1};
        case 'v':
            return {1, 0};
        default:
            return {0, 0};
    }
}

void Game::healEnemies() {
    for (auto it = enemies.begin(); it != enemies.end();) {
        if ((*it)->isAlive()) {
            (*it)->enemyRecover();
            ++it;
        } else {
            it = enemies.erase(it);
        }
    }
}

void Game::drawSpell() {
    char playerInitialState = board.getPlayer(player);

    int rangeL = player.getY() - player.getSpell2(), rangeR = player.getY() + player.getSpell2();
    int lineUp = player.getX() - 1, lineDown = player.getX() + 1;

    for (int i = rangeL; i <= rangeR; i++)
        if (borders(player.getX(), i)) {
            if (!board.checkValue(player.getX(), i, 'L') && !board.checkValue(player.getX(), i, 'a') && !board.checkValue(player.getX(), i, 'f'))
                board.update(player.getX(), i, 'O');
        }

    rangeL++, rangeR--;

    for (int i = 1; i <= player.getSpell2(); i++) {
        for (int j = rangeL; j <= rangeR; j++) {
            if (borders(lineUp, j))
                if (!board.checkValue(lineUp, j, 'L') && !board.checkValue(lineUp, j, 'a') && !board.checkValue(lineUp, j, 'f'))
                    board.update(lineUp, j, 'O');

            if (borders(lineDown, j))
                if (!board.checkValue(lineDown, j, 'L') && !board.checkValue(lineDown, j, 'a') && !board.checkValue(lineDown, j, 'f'))
                    board.update(lineDown, j, 'O');
        }

        lineUp--, lineDown++, rangeL++, rangeR--;
    }

    board.update(player.getX(), player.getY(), playerInitialState);
}