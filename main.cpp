
#include "./headers/Menu.h"
#include "./headers/Exceptions.h"
#include <iostream>

int main() {
    try {
        std::shared_ptr<Menu> menu = Menu::getGameInstance();
        menu->init();
    } catch(const TextureError& err) {
        std::cerr << err.what();
    } catch(const FontError& err) {
        std::cerr << err.what();
    } catch(const LogicError& err) {
        std::cerr << err.what();
    } catch(const CastError& err) {
        std::cerr << err.what();
    }
}
