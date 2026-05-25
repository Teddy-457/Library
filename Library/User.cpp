#include <string>
#include <fstream>
#include "User.hpp"
#include "Client.hpp"
#include "Admin.hpp"
#include "FileHandler.hpp"

User* User::deserialize(std::string filename, unsigned line) {
    std::ifstream file(filename, std::ios::in);
    FileHandler::checkIfOpen(file);


}