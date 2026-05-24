#include <fstream>
#include "FileHandler.hpp"
#include "Client.hpp"

void Client::serialize(std::string filename) const {
    ///std::ifstream file(filename, std::ios::in);
    ///FileHandler::checkIfOpen(file);
    ///Check if it already exists before writing
    
    std::ofstream file(filename, std::ios::app);
    FileHandler::checkIfOpen(file);
    file << m_username << '\n' << m_password << '\n' << m_admin << '\n';
    file.close();
}

void Client::deserialize(std::string filename) {

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