#pragma once
#include <string>

class User {
protected:
    std::string m_username;
    std::string m_password;
    bool m_admin;

    static constexpr char m_DELIMITER{ '$' };

    User(std::string, std::string, bool);

public:
    virtual void serialize(const std::string&) const = 0;
    static User* deserialize(const std::string&, unsigned);

    std::string getUsername() const;
    std::string getPassword() const;
    bool isAdmin() const;

    virtual ~User() = default;
};