#include <vector>
#include "Admin.hpp"

///Бонус:
///при въвеждане на паролата на екрана да се изписва  символа * вместо реалния символ
///при сортиране на книгите по зададен критерий, да се напише алгоритъм различен от пряка селекция и метода на мехурчето
///Търсене на книга по зададен критерий да игнорира регистъра на буквите (малки или големи)


int main() {
    //while (true) {
        Admin* admin = new Admin{ "admin", "i<3c++" };
        Client* client = new Client{ "client", "bbb" };

        std::vector<User*> users;
        users.push_back(admin);
        users.push_back(client);

        for (const auto* u : users) {
            u->serialize("Library.dat");
        }

        delete client;
        delete admin;
    //}
    return 0;
}