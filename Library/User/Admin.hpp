#pragma once
#include "Client.hpp"

class Admin : public Client {
public:
    Admin() = delete;
    Admin(std::string, std::string);

    static Admin* deserialize(std::ifstream&);
};
