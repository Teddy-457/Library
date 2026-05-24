#pragma once

#include <string>
#include "User.hpp"

class Client : public User {
public:
    //Client(std::string, std::string, bool);
    Client::Client(std::string username, std::string password, bool admin) : m_username(username), m_password(password), m_admin(admin) {}

    void virtual logout() const override;
    void virtual booksAll() const override;
    void virtual booksFind() const override;
    void virtual booksSort() const override;
    void virtual booksView() const override;

    void virtual booksAdd() const override;
    void virtual booksRemove() const override;
    void virtual usersAdd() const override;
    void virtual usersRemove() const override;
};
