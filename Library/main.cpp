#include <vector>
#include "Admin.hpp"
#include "Book.hpp"

///Бонус:
///при въвеждане на паролата на екрана да се изписва  символа * вместо реалния символ
///при сортиране на книгите по зададен критерий, да се напише алгоритъм различен от пряка селекция и метода на мехурчето
///Търсене на книга по зададен критерий да игнорира регистъра на буквите (малки или големи)


int main() {
    //while (true) {
        std::vector<User*> users;
        std::vector<Book> books;

        Admin* admin = new Admin{ "admin", "i<3c++" };
        Client* client = new Client{ "client", "bbb" };

        users.push_back(admin);
        users.push_back(client);

        //for (const auto* u : users) {
        //    u->serialize("Library.dat");
        //}

        User* copy_of_admin = User::deserialize("Library.dat", 0);
        User* copy_of_client = User::deserialize("Library.dat", 1);

        users.push_back(copy_of_client);
        users.push_back(copy_of_admin);

        delete copy_of_client;
        delete copy_of_admin;
        delete client;
        delete admin;
    //}
    return 0;
}