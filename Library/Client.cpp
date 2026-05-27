#include <fstream>
#include <string>
#include "Utilities.hpp"
#include "Client.hpp"

Client::Client(std::string username, std::string password, bool) : User(username, password, true) {} //protected
Client::Client(std::string username, std::string password) : User(username, password, false) {}      //public

void Client::serialize(const std::string& filename) const {
    if(m_username == "admin") { return; }

    std::ofstream file(filename, std::ios::app);
    Utilities::checkIfOpen(file);
    file << m_DELIMITER << m_admin << m_DELIMITER << m_username << m_DELIMITER << m_password << '\n';
    file.close();
}

Client* Client::deserialize(std::ifstream& file) {
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

    return new Client{ username, password };
}