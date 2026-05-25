#pragma once
#include <string>
#include "User.hpp"

class Client : public User {
protected:
    Client(std::string username, std::string password, bool) : User(username, password, true) {}

public:
    Client() = delete; //Client() : User("", "", false) {}
    Client(std::string username, std::string password) : User(username, password, false) {}

    void virtual serialize(std::string) const final;
    static Client* deserialize(std::ifstream&);
};
