#pragma once
#include <string>

class User {
protected:
    std::string m_username;
    std::string m_password;
    bool m_admin;

    User(std::string username, std::string password, bool admin) : m_username(username), m_password(password), m_admin(admin) {}

public:
    void virtual serialize(std::string) const = 0;
    void virtual deserialize(std::string) = 0;

    void virtual logout() const = 0;
    void virtual booksAll() const = 0;
    void virtual booksFind() const = 0;
    void virtual booksSort() const = 0;
    void virtual booksView() const = 0;

    void virtual booksAdd() const = 0;
    void virtual booksRemove() const = 0;
    void virtual usersAdd() const = 0;
    void virtual usersRemove() const = 0;
};