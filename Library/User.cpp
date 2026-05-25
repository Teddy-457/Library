#include <string>
#include <fstream>
#include <limits>
#include "User.hpp"
#include "Client.hpp"
#include "Admin.hpp"
#include "Utilities.hpp"

User* User::deserialize(std::string filename, unsigned line) {
    std::ifstream file(filename, std::ios::in);
    Utilities::checkIfOpen(file);

    for (unsigned i = 0; i < line; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    char check = file.get();
    if (check == m_DELIMITER) {
        char type = file.get();
        file.ignore(1);
        switch (type) {
            case '0':
                return Client::deserialize(file);
            case '1':
                return Admin::deserialize(file);
            default:
                file.close();
                Utilities::logAndThrow("Invalid file format");
        }
    }
    else {
        file.close();
        Utilities::logAndThrow("Tried to deserialize a book in place of a user");
    }
}

std::string User::getUsername() const {
    return m_username;
}
