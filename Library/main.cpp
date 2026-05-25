#include <vector>
#include "Library.hpp"

///Бонус:
///при въвеждане на паролата на екрана да се изписва  символа * вместо реалния символ
///при сортиране на книгите по зададен критерий, да се напише алгоритъм различен от пряка селекция и метода на мехурчето
///Търсене на книга по зададен критерий да игнорира регистъра на буквите (малки или големи)


int main() {
    //while (true) {
        Library lib;
        lib.usersAdd(new Client{ "client", "bbb" });

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