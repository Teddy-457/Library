#pragma once
#include <string>
#include "User.hpp"

class Client : public User {
protected:
    Client(std::string, std::string, bool);

public:
    Client() = delete;
    Client(const Client&) = delete;
    Client& operator=(const Client&) = delete;
    Client(Client&&) noexcept = delete;
    Client& operator=(Client&&) noexcept = delete;
    ~Client() override = default;

    Client(std::string, std::string);

    void serialize(const std::string&) const final;
    static Client* deserialize(std::ifstream&);
};
