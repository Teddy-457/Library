#pragma once
#include "Client.hpp"

class Admin : public Client {
public:
    Admin(std::string username, std::string password) : Client(username, password, true) {}

    void virtual serialize() const final;
    void virtual deserialize() final;

    void virtual booksAdd() const final;
    void virtual booksRemove() const final;
    void virtual usersAdd() const final;
    void virtual usersRemove() const final;
};
