#include <fstream>
#include <limits>
#include <stdexcept>
#include <iostream>/////////////////////////////////
#include "FileHandler.hpp"
#include "Client.hpp"

void Client::serialize(std::string filename) const {
    ///std::ifstream file(filename, std::ios::in);
    ///FileHandler::checkIfOpen(file);
    ///Check if it already exists before writing
    
    std::ofstream file(filename, std::ios::app);
    FileHandler::checkIfOpen(file);
    file << '$' << m_admin << '$' << m_username << '$' << m_password << '\n';
    file.close();
}

Client* Client::deserialize(std::string filename, unsigned line) {
    std::ifstream file(filename, std::ios::in);
    FileHandler::checkIfOpen(file);
    for (int i = 0; i < line; ++i) {
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "skipped line " << i << '\n';
    }
    char check = file.get();
    if (check == '$') {
        //file >> m_username;
    }
    else {
        std::cout << "Tried to deserialize a book in place of a user";
        throw std::runtime_error("Tried to deserialize a book in place of a user");
    }
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