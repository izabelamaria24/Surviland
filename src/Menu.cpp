#include "../headers/Menu.h"

void Menu::handlePlay(sf::RenderWindow& window) {
    Board board(10, 10);
    Player player(board.getHeight()  / 2, board.getWidth() / 2, 10, 0);

    std::shared_ptr<Game> game = Game::getGameInstance();

    game->build(board, player);
    game->start(window);
}

void Menu::handleStats(sf::RenderWindow& window) {
    sf::Font font;
    if (!font.loadFromFile("fonts/Roboto-Black.ttf")) {
        throw FontError("Could not load stats font!");
    }

    sf::Text statsTitle("Game Stats", font, 50);
    statsTitle.setOrigin(statsTitle.getLocalBounds().width / 2, statsTitle.getLocalBounds().height / 2);
    statsTitle.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 4);

    sf::Text backOption("Back (B)", font, 35);
    backOption.setOrigin(backOption.getLocalBounds().width / 2, backOption.getLocalBounds().height / 2);
    backOption.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) - 100);

    Parser parser;
    std::vector<GameData> gameDataList = parser.loadGameData("game_data.json");

    std::vector<sf::Text> statsTexts;
    for (size_t i = 0; i < gameDataList.size(); ++i) {
        sf::Text statsText("Level: " + std::to_string(gameDataList[i].level) + "\nAbility: " + std::to_string(gameDataList[i].ability) + "\nDate: " + gameDataList[i].date +
                           "\nVictory: " + std::string(gameDataList[i].win ? "Yes" : "No"), font, 25);
        statsText.setOrigin(statsText.getLocalBounds().width / 2, statsText.getLocalBounds().height / 2);
        statsText.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2 + static_cast<float>(i) * 60);
        statsTexts.push_back(statsText);
    }

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::B) {
                    display();
                    return;
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();

        window.draw(statsTitle);
        for (const auto& statsText : statsTexts)
            window.draw(statsText);

        window.draw(backOption);

        window.display();
    }
}


void Menu::display() {
    sf::RenderWindow window(sf::VideoMode::getFullscreenModes()[0], "Surviland", sf::Style::Fullscreen);
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("fonts/Roboto-Black.ttf")) {
        throw FontError("Could not load menu font!");
    }

    sf::Text title("Surviland", font, 100);
    title.setOrigin(title.getLocalBounds().width / 2, title.getLocalBounds().height / 2);
    title.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 4);

    sf::Text playOption("Play (P)", font, 35);
    playOption.setOrigin(playOption.getLocalBounds().width / 2, playOption.getLocalBounds().height / 2);
    playOption.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2);

    sf::Text statsOption("Stats (S)", font, 35);
    statsOption.setOrigin(statsOption.getLocalBounds().width / 2, statsOption.getLocalBounds().height / 2);
    statsOption.setPosition(static_cast<float>(window.getSize().x) / 2, static_cast<float>(window.getSize().y) / 2 + 60);

    while (window.isOpen()) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::P) {
                    handlePlay(window);
                    return;
                } else if (event.key.code == sf::Keyboard::S) {
                    handleStats(window);
                    return;
                } else if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
            }
        }

        window.clear();

        window.draw(title);
        window.draw(playOption);
        window.draw(statsOption);

        window.display();
    }
}


void Menu::init() {
    display();
}
