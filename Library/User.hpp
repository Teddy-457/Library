#pragma once

#include <string>

class User {
protected:
    std::string m_username;
    std::string m_password;
    bool admin;

public:
    void logout() const;
    void booksAll() const;
    void booksFind() const;
    void booksSort() const;
    void booksView() const;

    void virtual booksAdd() const = 0;
    void virtual booksRemove() const = 0;
    void virtual usersAdd() const = 0;
    void virtual usersRemove() const = 0;
};