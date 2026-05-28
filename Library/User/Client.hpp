#pragma once
#include <string>
#include "User.hpp"

class Client : public User {
protected:
    Client(std::string, std::string, bool);

public:
    Client() = delete;
    Client(std::string, std::string);

    void serialize(const std::string&) const final;
    static Client* deserialize(std::ifstream&);
};
