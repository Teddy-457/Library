#pragma once
#include <string>

class User {
protected:
    std::string m_username;
    std::string m_password;
    bool m_admin;

    static constexpr char m_DELIMITER{ '$' };

    User(std::string username, std::string password, bool admin) : m_username(username), m_password(password), m_admin(admin) {}

public:
    void virtual serialize(std::string) const = 0;
    static User* deserialize(std::string, unsigned);

    virtual ~User() = default;
};