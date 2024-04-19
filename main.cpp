
#include <SFML/Graphics.hpp>
#include "./headers/Menu.h"

int main() {

    window.setVerticalSyncEnabled(true);
    
    std::shared_ptr<Menu> menu = Menu::getGameInstance();
    menu->init();

//     while(window.isOpen()) {
//         bool shouldExit = false;
//         sf::Event e{};
//         while(window.pollEvent(e)) {
//             switch(e.type) {
//             case sf::Event::Closed:
//                 window.close();
//                 break;
//             case sf::Event::Resized:
//                 std::cout << "New width: " << window.getSize().x << '\n'
//                           << "New height: " << window.getSize().y << '\n';
//                 break;
//             case sf::Event::KeyPressed:
//                 std::cout << "Received key " << (e.key.code == sf::Keyboard::X ? "X" : "(other)") << "\n";
//                 if(e.key.code == sf::Keyboard::Escape)
//                     shouldExit = true;
//                 break;
//             default:
//                 break;
//             }
//         }
//         if(shouldExit) {
//             window.close();
//             break;
//         }
//         using namespace std::chrono_literals;
//         std::this_thread::sleep_for(300ms);
//
//         window.clear();
//         window.display();
//     }
     return 0;
}
