#include "../headers/Game.h"
#include "../headers/SmartEnemy.h"
#include "../headers/DumbEnemy.h"
#include "../headers/ObstacleEnemy.h"

void Game::addObservers() {
    observers.emplace_back(std::make_shared<PlayerController>(*this));
    observers.emplace_back(std::make_shared<EnemyController>(*this));
    observers.emplace_back(std::make_shared<PowerUpController>(*this));
}

void Game::notifyObservers(EventData &eventData, const std::string &observerType) {
    for (const auto& observer : observers)
        observer->update(eventData, observerType);
}

std::pair<int, int> Game::generateCoordinates() {
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());

    int width = board.getWidth();
    int height = board.getHeight();

    std::uniform_int_distribution<int> disX(1, width);
    std::uniform_int_distribution<int> disY(1, height);

    int x = disX(gen);
    int y = disY(gen);

    return std::make_pair(x, y);
}

std::pair<int, int> Game::generateEnemyAttributes() {
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dis(1, 1);

    int hp = dis(gen), dmg = dis(gen);
    return std::make_pair(hp, dmg);
}

void Game::generateDirection(EventData& eventData) {
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dis(0, 3);

    int val = dis(gen);
    if (val == 0) eventData.dir = 'U';
    if (val == 1) eventData.dir = 'D';
    if (val == 2) eventData.dir = 'R';
    if (val == 3) eventData.dir = 'L';
}

void Game::generate(EventData& eventData) {
    std::pair<int, int> coord = generateCoordinates();
    std::pair<int, int> attributes = generateEnemyAttributes();
    generateDirection(eventData);

    eventData.x = coord.first;
    eventData.y = coord.second;
    eventData.dmg = attributes.second;
    eventData.hp = attributes.first;
}

void Game::spawn() {
    static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> dis(0, 99);

    int randomNum = dis(gen);

    if (randomNum < 50) return;

    // probabilities
    int dumbEnemyThreshold = 60;
    int smartEnemyThreshold = 77;
    int healThreshold = 79;
    int armorThreshold = 81;
    int stopwatchThreshold = 85;
    int jackpotThreshold = 87;
    int dumbEnemyHoardThreshold = 92;
    int obstacleThreshold = 94;
    int smartEnemyHoardThreshold = 96;
    int portalThreshold = 99;

    EventData eventData;
    time++;

    if (randomNum < dumbEnemyThreshold) {
        eventData.name = "SF";
        generate(eventData);
        notifyObservers(eventData, "Enemy");
    } else if (randomNum < smartEnemyThreshold) {
        eventData.name = "ST";
        generate(eventData);
        notifyObservers(eventData, "Enemy");
    } else if (randomNum < healThreshold) {
        eventData.name = "SD";
        generate(eventData);
        eventData.type = "H";
        notifyObservers(eventData, "PowerUp");
    } else if (randomNum < armorThreshold) {
        eventData.name = "SD";
        generate(eventData);
        eventData.type = "A";
        notifyObservers(eventData, "PowerUp");
    } else if (randomNum < stopwatchThreshold) {
        eventData.name = "SD";
        generate(eventData);
        eventData.type = "F";
        notifyObservers(eventData, "PowerUp");
    } else if (randomNum < jackpotThreshold){
        eventData.name = "SD";
        generate(eventData);
        eventData.type = "M";
        notifyObservers(eventData, "PowerUp");
    } else if (randomNum < dumbEnemyHoardThreshold) {
        eventData.name = "SWF";
        generate(eventData);
        notifyObservers(eventData, "Enemy");}
    else if (randomNum < obstacleThreshold) {
        eventData.name = "SO";
        generate(eventData);
        notifyObservers(eventData, "Obstacle");
    }
    else if (randomNum < smartEnemyHoardThreshold){
        eventData.name = "SWT";
        generate(eventData);
        notifyObservers(eventData, "Enemy");
    } else if (randomNum < portalThreshold) {
        std::pair<int, int>pair1 = generateCoordinates();
        std::pair<int, int>pair2 = generateCoordinates();

        std::shared_ptr<Portal> newPortal = std::make_shared<Portal>(pair1.first, pair1.second, pair2.first, pair2.second, 5);
        addPortal(newPortal);
    }
}

void Game::clearScreen(sf::RenderWindow& window) {
    window.clear();
}

void Game::start(sf::RenderWindow& window) {
    window.setActive(true);

    while (window.isOpen()) {
        update();
        if (checkVictory()) {
            win();
            renderVictory(window);
        }

        if (player.isDead()) {
            gameOver = true;
            renderLose(window);
        }

        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                    return;
                }
            }

            if (!gameOver) {
                if (event.type == sf::Event::KeyPressed) {
                    player.decreaseTime();
                    EventData eventData;
                    time++;
                    if (event.key.code == sf::Keyboard::W) {
                        eventData.name = "M";
                        eventData.dir = 'U';
                        notifyObservers(eventData, "Player");
                    } else if (event.key.code == sf::Keyboard::A) {
                        eventData.name = "M";
                        eventData.dir = 'L';
                        notifyObservers(eventData, "Player");
                    } else if (event.key.code == sf::Keyboard::D) {
                        eventData.name = "M";
                        eventData.dir = 'R';
                        notifyObservers(eventData, "Player");
                    } else if (event.key.code == sf::Keyboard::S) {
                        eventData.name = "M";
                        eventData.dir = 'D';
                        notifyObservers(eventData, "Player");
                    } else if (event.key.code == sf::Keyboard::B) {
                        eventData.name = "ATT";
                        notifyObservers(eventData, "Player");
                    } else if (event.key.code == sf::Keyboard::L) {
                        eventData.name = "UP";
                        eventData.type = "L";
                        notifyObservers(eventData, "Player");
                    } else if (event.key.code == sf::Keyboard::O) {
                        eventData.name = "UP";
                        eventData.type = "O";
                        notifyObservers(eventData, "Player");
                    } else if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }

                    if (!player.checkTime())
                        spawn();

                    clearScreen(window);
                    render(window);
                    window.display();
                }
            }
        }
    }
}

void Game::renderLose(sf::RenderWindow &window) {
    sf::Texture loseTexture;
    if (!loseTexture.loadFromFile("../assets/gameover.png")) {
        throw TextureError("Can not load asset");
    }

    sf::RectangleShape loseItem(sf::Vector2f(500, 500));
    loseItem.setTexture(&loseTexture);
    loseItem.setOrigin(loseItem.getLocalBounds().width / 2, loseItem.getLocalBounds().height / 2);
    loseItem.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);

    window.clear();
    window.draw(loseItem);
    window.display();
}

void Game::renderVictory(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("fonts/Roboto-Black.ttf")) {
        throw FontError("Can not load font");
    }

    sf::Text victoryText("VICTORY!", font, 35);
    victoryText.setOrigin(victoryText.getLocalBounds().width / 2, victoryText.getLocalBounds().height / 2);
    victoryText.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 4);

    sf::Texture victoryTexture;
    if (!victoryTexture.loadFromFile("assets/trophy.png")) {
        throw TextureError("Can not load asset");
    }

    sf::RectangleShape victoryItem(sf::Vector2f(300, 300));
    victoryItem.setTexture(&victoryTexture);
    float itemPosX = victoryText.getPosition().x - victoryItem.getLocalBounds().width / 2;
    float itemPosY = victoryText.getPosition().y + victoryText.getLocalBounds().height / 2 + 30;
    victoryItem.setPosition(itemPosX, itemPosY);

    window.clear();
    window.draw(victoryText);
    window.draw(victoryItem);
    window.display();
}

std::shared_ptr<Enemy> Game::checkEnemy(int x, int y) {
    for (auto& enemy: enemies)
        if (enemy->getX() == x && enemy->getY() == y) return enemy;

    throw GameError("No enemy found");
}

void Game::render(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("fonts/Roboto-Black.ttf")) {
        throw FontError("Can not load font");
    }

    // Load the background image
    sf::Texture playerTextureUp;
    if (!playerTextureUp.loadFromFile("assets/up_penguin.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture playerTextureDown;
    if (!playerTextureDown.loadFromFile("assets/down_penguin.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture playerTextureLeft;
    if (!playerTextureLeft.loadFromFile("assets/left_penguin.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture playerTextureRight;
    if (!playerTextureRight.loadFromFile("assets/right_penguin.jpg")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture dumbEnemyTexture;
    if (!dumbEnemyTexture.loadFromFile("assets/hogrider.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture smartEnemyTexture;
    if (!smartEnemyTexture.loadFromFile("assets/smartenemy.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture spellTexture;
    if (!spellTexture.loadFromFile("assets/spell.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture attackTexture;
    if (!attackTexture.loadFromFile("assets/attack.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture deadEnemyTexture;
    if (!deadEnemyTexture.loadFromFile("assets/dead.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture moneyTexture;
    if (!moneyTexture.loadFromFile("assets/money.jpg")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture jackpotTexture;
    if (!jackpotTexture.loadFromFile("assets/jackpot.jpg")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture stopwatchTexture;
    if (!stopwatchTexture.loadFromFile("assets/stopwatch.jpg")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture armorTexture;
    if (!armorTexture.loadFromFile("assets/armor.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture healTexture;
    if (!healTexture.loadFromFile("assets/hp.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture heartTexture;
    if (!heartTexture.loadFromFile("assets/heart.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture emptyHeartTexture;
    if (!emptyHeartTexture.loadFromFile("assets/empty_heart.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture coinTexture;
    if (!coinTexture.loadFromFile("assets/coin.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture portalTexture;
    if (!portalTexture.loadFromFile("assets/portal.png")) {
        throw TextureError("Can not load asset");
    }

    sf::Texture obstacleTexture;
    if (!obstacleTexture.loadFromFile("assets/obstacle.png")) {
        throw TextureError("Can not load asset");
    }

    const int cellSize = 80;
    for (int i = 1; i <= board.getHeight(); ++i) {
        for (int j = 1; j <= board.getWidth(); ++j) {
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setPosition(static_cast<float>(i) * cellSize, static_cast<float>(j) * cellSize);
            cell.setOutlineThickness(2);
            cell.setOutlineColor(sf::Color::Red);
            cell.setFillColor(sf::Color::White);

            // player
            if (player.getX() == j && player.getY() == i) {

                if (board.checkValue(player.getX(), player.getY(), '^'))
                    cell.setTexture(&playerTextureUp);

                else if (board.checkValue(player.getX(), player.getY(), '<'))
                    cell.setTexture(&playerTextureLeft);

                else if (board.checkValue(player.getX(), player.getY(), 'v'))
                    cell.setTexture(&playerTextureDown);

                else cell.setTexture(&playerTextureRight);
            }

                // attacks
            else if (board.checkValue(j, i, 'O'))
                cell.setTexture(&spellTexture);
            else if (board.checkValue(j, i, 'L'))
                cell.setTexture(&attackTexture);

                // enemies
            else if (board.checkValue(j, i, 'x'))
                cell.setTexture(&deadEnemyTexture);
            else if (board.checkValue(j, i, '+')) {
                std::shared_ptr<Enemy> temp = checkEnemy(j, i);
                if (std::dynamic_pointer_cast<SmartEnemy>(temp)) {
                    cell.setTexture(&smartEnemyTexture);
                }
                else if (std::dynamic_pointer_cast<DumbEnemy>(temp)) {
                    cell.setTexture(&dumbEnemyTexture);
                } else {
                    throw CastError("Failed to cast Enemy into SmartEnemy or DumbEnemy");
                }
            }

            else if (board.checkValue(j, i, 'p')) {
                cell.setTexture(&portalTexture);
            }
            else if (board.checkValue(j, i, 'o') ) {
                cell.setTexture(&obstacleTexture);
            }

                // powerups
            else if (board.checkValue(j, i, '$')) {
                cell.setTexture(&moneyTexture);
            }
            else if (board.checkValue(j, i, 'm') || board.checkValue(j, i, 'M')) {
                cell.setTexture(&jackpotTexture);
            }
            else if (board.checkValue(j, i, 'f') || board.checkValue(j, i, 'F')) {
                cell.setTexture(&stopwatchTexture);
            }
            else if (board.checkValue(j, i, 'a') || board.checkValue(j, i, 'A')) {
                cell.setTexture(&armorTexture);
            }
            else if (board.checkValue(j, i, 'h') || board.checkValue(j, i, 'H')) {
                cell.setTexture(&healTexture);
            }

            if (board.checkValue(j, i, 'm') || board.checkValue(j, i, 'f') || board.checkValue(j, i, 'a')
                || board.checkValue(j, i, 'h') || board.checkValue(j, i, '$')) cell.setOutlineColor(sf::Color::Green);

            window.draw(cell);
        }
    }

    sf::Text timeText("Time " + std::to_string(time), font, 35);

    sf::Text hpText("Hp: ", font, 35);
    std::vector<sf::RectangleShape> hpRectangles;
    std::vector<sf::RectangleShape> coinSprites;

    hpText.setPosition(static_cast<float>(window.getSize().x) - hpText.getLocalBounds().width - 20, timeText.getPosition().y + timeText.getLocalBounds().height + 30);

    float startX = static_cast<float>(window.getSize().x) - 30 * (10 + 1) - 5 * 10;
    float startY = hpText.getPosition().y + hpText.getLocalBounds().height + 20;

    for (int i = 0; i < 10; ++i) {
        sf::RectangleShape rect(sf::Vector2f(30, 30));
        if (i < player.getHP())
            rect.setTexture(&heartTexture);
        else
            rect.setTexture(&emptyHeartTexture);

        float posX = startX + static_cast<float>(i) * (30 + 5);
        rect.setPosition(posX, startY);
        hpRectangles.push_back(rect);
    }

    sf::Text armorText("Armor: " + std::to_string(player.getArmor()), font, 35);
    sf::Text rangeText("Ability range: " + std::to_string(player.getRange()), font, 35);
    sf::Text levelText("Level: " + std::to_string(player.getLevel()), font, 35);
    sf::Text stopwatchText("Stopwatch activated: " + std::to_string(static_cast<int>(player.checkTime())), font, 35);
    sf::Text moneyText("Money: ", font, 35);

    timeText.setPosition(static_cast<float>(window.getSize().x) - timeText.getLocalBounds().width - 20, 20);
    hpText.setPosition(static_cast<float>(window.getSize().x) - hpText.getLocalBounds().width - 20, timeText.getPosition().y + timeText.getLocalBounds().height + 20);
    armorText.setPosition(static_cast<float>(window.getSize().x) - armorText.getLocalBounds().width - 20, hpText.getPosition().y + hpText.getLocalBounds().height + 40);
    rangeText.setPosition(static_cast<float>(window.getSize().x) - rangeText.getLocalBounds().width - 20, armorText.getPosition().y + armorText.getLocalBounds().height + 20);
    levelText.setPosition(static_cast<float>(window.getSize().x) - levelText.getLocalBounds().width - 20, rangeText.getPosition().y + rangeText.getLocalBounds().height + 20);
    stopwatchText.setPosition(static_cast<float>(window.getSize().x) - stopwatchText.getLocalBounds().width - 20, levelText.getPosition().y + levelText.getLocalBounds().height + 20);
    moneyText.setPosition(static_cast<float>(window.getSize().x) - moneyText.getLocalBounds().width - 20, stopwatchText.getPosition().y + stopwatchText.getLocalBounds().height + 20);

    startX = static_cast<float>(window.getSize().x) - static_cast<float>(30 * (player.getMoney() + 1)) - static_cast<float>(5 * player.getMoney());
    startY = moneyText.getPosition().y + moneyText.getLocalBounds().height + 20;

    for (int i = 0; i < player.getMoney(); ++i) {
        sf::RectangleShape coinSprite(sf::Vector2f(30, 30));
        coinSprite.setTexture(&coinTexture);
        coinSprite.setPosition(startX + static_cast<float>(i) * (30 + 5), startY);
        coinSprites.push_back(coinSprite);
    }


    window.draw(timeText);
    window.draw(hpText);

    for (const auto& rect : hpRectangles) {
        window.draw(rect);
    }

    window.draw(armorText);
    window.draw(rangeText);
    window.draw(levelText);
    window.draw(stopwatchText);
    window.draw(moneyText);

    for (const auto& item : coinSprites) {
        window.draw(item);
    }
}

bool Game::borders(int x, int y) {
    return x >= 1 && x <= board.getWidth() && y >= 1 && y <= board.getHeight();
}

void Game::update() {
    while (player.updateAvailable()) {
        player.levelUp();
        player.increaseAvailableUpgrades();
        player.payUpgrade();
    }
}

bool Game::checkVictory() const {
    return time >= 250;
}

void Game::win() {
    outputMessage = "VICTORY!";
    gameOver = true;
}

void Game::markEnemies() {
    for (const auto& enemy : enemies)
        if (enemy->isAlive()) {
            if (enemy->isHit()) board.update(enemy->getX(), enemy->getY(), 'x');
            else board.update(enemy->getX(), enemy->getY(), '+');
        }
}

void Game::markPortals() {
    for (const auto& portal : portals) {
        if (!portal->destroyed()) {
            board.update(portal->getX(), portal->getY(), 'p');
            board.update(portal->getX2(), portal->getY2(), 'p');
        }
    }
}

void Game::markObstacles() {
    for (const auto& obstacle : enemies) {
        if (std::dynamic_pointer_cast<ObstacleEnemy>(obstacle)) {
            board.update(obstacle->getX(), obstacle->getY(), 'o');
        }
    }
}

void Game::moveEnemies() {
    if (player.checkTime()) return;

    for (auto& enemy : enemies){
        enemy->changeDirection(board, player);
        int x = enemy->getX(), y = enemy->getY();
        enemy->goBack(board, player);

        if (!(x == player.getX() && y == player.getY())) {
            board.checkAndUpdate(enemy->getX(), enemy->getY());
            if (board.noMarks(enemy->getX(), enemy->getY())) board.update(enemy->getX(), enemy->getY(), '.');
            enemy->changeDirection(board, player);
        } else {
            if (enemy->isAlive() && !board.checkValue(enemy->getX(), enemy->getY(), 'L')) {
                player.decreaseHp(enemy->attackDamage());
            }
        }
    }
}

void Game::addPortal(const std::shared_ptr<Portal> &portal) {
    portals.emplace_back(portal);
}

void Game::checkPortal() {
    for (const auto& portal : portals) {
        if (portal->getX() == player.getX() && portal->getY() == player.getY()) {
            player.move(portal->getX2(), portal->getY2());
            portal->use();
            break;
        } else if (portal->getX2() == player.getX() && portal->getY2() == player.getY()) {
            player.move(portal->getX(), portal->getY());
            portal->use();
            break;
        }
    }
}

bool Game::checkCollision(int x, int y) const {
    for (const auto &enemy : enemies) {
        if (enemy->getX() == x && enemy->getY() == y) {
            return true;
        }
    }

    bool hasPowerUp = std::any_of(powerUps.begin(), powerUps.end(), [&](const auto &powerup) {
        return powerup->getX() == x && powerup->getY() == y;
    });

    if (hasPowerUp)
        return true;
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

//    const int dx[] = {-1, 1, 0, 0};
//    const int dy[] = {0, 0, -1, 1};

    for (int i = 1; i <= player.getAbility(); i++) {
        newX += addX;
        newY += addY;

        if (borders(newX, newY))
            if (board.checkValue(newX, newY, 'L')) board.update(newX, newY, '.');
    }

    if (player.availableSpell()) clearSpell();

    for (int i = 1; i <= board.getHeight(); i++)
        for (int j = 1; j <= board.getWidth(); j++)
            board.checkAndUpdate(i, j);
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

void Game::collectMoney() {
    board.collect(player.getX(), player.getY(), '$', player);
}

void Game::collectHP() {
    board.collect(player.getX(), player.getY(), 'h', player);
}

void Game::collectArmor() {
    board.collect(player.getX(), player.getY(), 'a', player);
}

void Game::collectStopwatch() {
    player.resetStopwatch();
    board.collect(player.getX(), player.getY(), 'f', player);
}

void Game::collectAllMoney() {
    for (int i = 1; i <= board.getHeight(); i++)
        for (int j = 1; j <= board.getWidth(); j++)
            if (board.checkMoney(i, j))
            {
                board.collect(i, j, '$', player);
                board.update(i, j, '.');
            }

    board.collect(player.getX(), player.getY(), 'm', player);
}

void Game::collectResources() {
    int x = player.getX(), y = player.getY();

    if (board.checkMoney(x, y)) collectMoney();
    if (board.checkArmor(x, y)) collectArmor();
    if (board.checkStopwatch(x, y)) collectStopwatch();
    if (board.checkHP(x, y)) collectHP();
    if (board.checkJackpot(x, y)) collectAllMoney();
}


void Game::changeEnemiesDirection() {
    for (auto& enemy: enemies) {
        if (auto smartEnemy = std::dynamic_pointer_cast<SmartEnemy>(enemy)) {
            smartEnemy->modifyDirection(board.getPlayer(player));
        }
        else if (auto dumbEnemy = std::dynamic_pointer_cast<DumbEnemy>(enemy)) {
            continue;
        }
        else {
            throw CastError("Failed to cast Enemy into Smart or Dumb Enemy");
        }
    }
}

void Game::markPowerUps() {
    for (auto it = powerUps.begin(); it != powerUps.end();) {
        auto& pwrUp = *it;
        std::string pwType = pwrUp->getType();

        int add = 0;
        if (pwrUp->dead()) add = 32;

        if (pwType == "H")
            board.update(pwrUp->getX(), pwrUp->getY(), static_cast<char>('H' + add));
        if (pwrUp->getType() == "A")
            board.update(pwrUp->getX(), pwrUp->getY(), static_cast<char>('A' + add));
        if (pwrUp->getType() == "M")
            board.update(pwrUp->getX(), pwrUp->getY(), static_cast<char>('M' + add));
        if (pwrUp->getType() == "F")
            board.update(pwrUp->getX(), pwrUp->getY(), static_cast<char>('F' + add));


        if (pwrUp->dead()) it = powerUps.erase(it);
        else it++;
    }
}

void Game::markEntities() {
    markPowerUps();
    markPortals();
    markObstacles();
    markEnemies();
}

void Game::addEnemy(const std::shared_ptr<Enemy>& newEnemy) {
    enemies.emplace_back(newEnemy);
}

void Game::addPowerup(int x, int y, int hp, const std::string &type) {
    auto newPowerup = std::make_shared<PowerUp>(x, y, hp, type);
    powerUps.emplace_back(newPowerup);
}

void Game::attackEnemies(int x, int y, char sym, bool& enemyFound, bool& stillAlive) {
    for (auto &enemy: enemies) {
        if (enemy->getX() == x && enemy->getY() == y) {

            if (!enemy->checkLastHit()) {
                enemy->hitEnemy(sym, player.getAbility(), player.getSpell1(), player.availableSpell());
                enemy->activateHit();
                if (!enemy->isAlive()) board.increase(x, y, '$', 2);
            }

            enemyFound = true;
            if (enemy->isAlive()) stillAlive = true;
        }
    }
}

void Game::takePowerups(int x, int y, char sym) {
    for (auto &powerup: powerUps) {
        if (powerup->getX() == x && powerup->getY() == y) {
            if (!powerup->checkLastHit()) {
                powerup->attack(sym, player.getAbility(), player.getSpell1(), player.availableSpell());
                powerup->activateHit();
            }
            if (powerup->dead()) {
                if (powerup->getType() == "H") board.increase(x, y, 'h', 1);
                if (powerup->getType() == "A") board.increase(x, y, 'a', 1);
                if (powerup->getType() == "M") board.increase(x, y, 'm', 1);
                if (powerup->getType() == "F") board.increase(x, y, 'f', 1);
            }
        }
    }
}

Board& Game::getBoard() {
    return board;
}

Player& Game::getPlayer() {
    return player;
}

void Game::build(const Board &initialBoard, const Player &initialPlayer) {
    board = initialBoard;
    player = initialPlayer;
    board.update(player.getX(), player.getY(), '^');
}

void Game::updateOutputMessage(const std::string &m) {
    outputMessage = m;
}
