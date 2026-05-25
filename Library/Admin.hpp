#pragma once
#include "Client.hpp"

class Admin : public Client {
public:
    Admin() = delete;
    //Admin() : Client("", "") {} //use protected Client constructor instead; if default constructor necessary
    Admin(std::string username, std::string password) : Client(username, password, true) {}

    static Admin* deserialize(std::ifstream&);

    void virtual booksAdd() const final;
    void virtual booksRemove() const final;
    void virtual usersAdd() const final;
    void virtual usersRemove() const final;
};
