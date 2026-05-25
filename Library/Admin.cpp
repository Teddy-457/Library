#include <fstream>
#include <string>
#include "Admin.hpp"

Admin* Admin::deserialize(std::ifstream& file) {
    std::string username;
    std::string password;

    char c = file.get();
    while (c != m_DELIMITER && c != '\n') {
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