#include <vector>
#include "Library.hpp"

///Бонус:
///при въвеждане на паролата на екрана да се изписва  символа * вместо реалния символ
///при сортиране на книгите по зададен критерий, да се напише алгоритъм различен от пряка селекция и метода на мехурчето
///Търсене на книга по зададен критерий да игнорира регистъра на буквите (малки или големи)

///commands with no prototypes:
///open, close, save, saveas, help, exit
///books view?

//verboseness toggle

int main() {
    //while (true) {
        Library lib;
        lib.usersAdd(new Client{ "client", "bbb" });
        lib.booksAdd(new Book{"Frank Herbert",
                              "Dune",
                              "Science Fiction",
                              "A mythic and emotionally charged hero's journey set on the desert planet Arrakis.",
                              1965,
                              Tags_t{"Sci-Fi", "Classic", "Space Opera", "Politics"},
                              4.54,
                              0441172717});

       //lib.usersRemove("client");

        //lib.booksInfo(0441172717);
        //lib.booksAll();

        //for (const auto* u : users) {
        //    u->serialize("Library.dat");
        //}

        //User* copy_of_admin = User::deserialize("Library.dat", 0);
        //User* copy_of_client = User::deserialize("Library.dat", 1);
        //delete copy_of_client;
        //delete copy_of_admin;
    //}
    return 0;
}