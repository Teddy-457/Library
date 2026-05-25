#include <fstream>
#include "Utilities.hpp"
#include "Client.hpp"

void Client::serialize(std::string filename) const {
    ///std::ifstream file(filename, std::ios::in);
    ///FileHandler::checkIfOpen(file);
    ///Check if it already exists before writing
    
    std::ofstream file(filename, std::ios::app);
    Utilities::checkIfOpen(file);
    file << '$' << m_admin << '$' << m_username << '$' << m_password << '\n';
    file.close();
}

///code from W2 HW
///char buf[128];
///const char* buf_ptr{ buf };
///while (file.getline(buf, 128)) {
///    int copy_cnt{};
///    while (*buf_ptr != ',') {
///        temp.group[current_group].first[copy_cnt++] = *buf_ptr;
///        ++buf_ptr;
///    } copy_cnt = 0; ++buf_ptr;
///
///    while (*buf_ptr != ',') {
///        temp.group[current_group].last[copy_cnt++] = *buf_ptr;
///        ++buf_ptr;
///    } copy_cnt = 0; ++buf_ptr;

Client* Client::deserialize(std::ifstream& file) {
    file.ignore(1);
    Client client;
    file >> client.m_username;

    file.close();
    return new Client(client);///
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