#include <fstream>
#include <string>
#include "Utilities.hpp"
#include "Client.hpp"

void Client::serialize(std::string filename) const {
    ///std::ifstream file(filename, std::ios::in);
    ///FileHandler::checkIfOpen(file);
    ///Check if it already exists before writing
    /// 
    /// check at Library level for duplicates instead !!

    std::ofstream file(filename, std::ios::app);
    Utilities::checkIfOpen(file);
    file << m_DELIMITER << m_admin << m_DELIMITER << m_username << m_DELIMITER << m_password << '\n';
    file.close();
}

Client* Client::deserialize(std::ifstream& file) {
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

    return new Client{ username, password };
}

void Client::logout() const {

}

void Client::booksAll() const {

}

void Client::booksFind() const {

}

void Client::booksSort() const {

}

void Client::booksView() const {
    
}

void Client::booksAdd() const {}
void Client::booksRemove() const {}
void Client::usersAdd() const {}
void Client::usersRemove() const {}