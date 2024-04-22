
#include "./headers/Menu.h"

int main() {
//    window.setVerticalSyncEnabled(true);
     std::shared_ptr<Menu> menu = Menu::getGameInstance();
     menu->init();
     return 0;
}
