#pragma once
#include <string>

class User {
protected:
    std::string m_username;
    std::string m_password;
    bool m_admin;

    User(std::string, std::string, bool);

public:
    static constexpr char m_DELIMITER{ '$' };

    virtual void serialize(const std::string&) const = 0;
    static User* deserialize(const std::string&, unsigned);

    const std::string& getUsername() const;
    const std::string& getPassword() const;
    bool isAdmin() const;

    virtual ~User() = default;
};