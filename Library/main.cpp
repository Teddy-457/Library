#include "Library&Menu/Library.hpp"
#include "Library&Menu/Menu.hpp"

int main() {
    Library lib;
    //lib.usersAdd(new Client{ "client", "bbb" });
    //lib.usersAdd(new Admin{ "johhny-bravo", "aaa" });
    //lib.booksAdd(new Book{"Frank Herbert", "Dune", "Science Fiction",
    //                      "A mythic and emotionally charged hero's journey set on the desert planet Arrakis.",
    //                      1965, Tags_t{"Sci-Fi", "Classic", "Space Opera", "Politics"}, 4.54, 441172717});

    Menu::menu(lib);

    return 0;
}