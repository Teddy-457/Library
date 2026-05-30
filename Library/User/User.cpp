#include "User.hpp"
#include <fstream>
#include <string>
#include "../Utilities.hpp"
#include "Client.hpp"
#include "Admin.hpp"

User::User(std::string username, std::string password, bool admin) : m_username(username), m_password(password), m_admin(admin) {}

User* User::deserialize(const std::string& filename, unsigned line) {
    std::ifstream file(filename, std::ios::in);
    Utilities::checkIfOpen(file);
    
    Utilities::skipLines(file, line);

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

const std::string& User::getUsername() const {
    return m_username;
}

const std::string& User::getPassword() const {
    return m_password;
}

bool User::isAdmin() const {
    return m_admin;
}