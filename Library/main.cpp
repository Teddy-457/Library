#include "Library&Menu/Library.hpp"
#include "Library&Menu/Menu.hpp"

int main() {
    //Library lib;
    //Menu::menu(lib);
    Book&& temp_book{ "Frank Herbert",
                              "Dune",
                              "Science Fiction",
                              "A mythic and emotionally charged hero's journey set on the desert planet Arrakis.",
                              1965,
                              Tags_t{"Sci-Fi", "Classic", "Space Opera", "Politics"},
                              4.54,
                              0441172717 };
    Book test_book(std::move(temp_book));
    return 0;
}