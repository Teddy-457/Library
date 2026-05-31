#include "Tests.hpp"

#ifdef DOCTEST_CONFIG_DISABLE
#include "Library&Menu/Library.hpp"
#include "Library&Menu/Menu.hpp"

int main() {
    Library lib;
    Menu::getInstance().menu(lib);

    return 0;
}
#endif