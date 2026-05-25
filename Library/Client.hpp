#pragma once
#include <string>
#include "User.hpp"

class Client : public User {
protected:
    Client(std::string username, std::string password, bool) : User(username, password, true) {}

public:
    Client() : User("", "", false) {}
    Client(std::string username, std::string password) : User(username, password, false) {}

    void virtual serialize(std::string) const final;
    static Client* deserialize(std::ifstream&);

    void virtual logout() const final;
    void virtual booksAll() const final;
    void virtual booksFind() const final;
    void virtual booksSort() const final;
    void virtual booksView() const final;

    void virtual booksAdd() const override;
    void virtual booksRemove() const override;
    void virtual usersAdd() const override;
    void virtual usersRemove() const override;
};
