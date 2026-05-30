#include "Admin.hpp"
#include <fstream>
#include <string>

Admin::Admin(std::string username, std::string password) : Client(username, password, true) {}

Admin* Admin::deserialize(std::ifstream& file) {
    std::string username;
    std::string password;

    char c = file.get();
    while (c != m_DELIMITER) {
        username.push_back(c);
        c = file.get();
    }
    c = file.get();
    while (c != '\n') {
        password.push_back(c);
        c = file.get();
    }
    file.close();

    return new Admin{ username,password };
}