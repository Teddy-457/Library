#pragma once
#include "Client.hpp"

class Admin : public Client {
public:
    Admin() = delete;
    Admin(const Admin&) = delete;
    Admin& operator=(const Admin&) = delete;
    Admin(Admin&&) noexcept = delete;
    Admin& operator=(Admin&&) noexcept = delete;
    ~Admin() override = default;

    Admin(std::string, std::string);

    static Admin* deserialize(std::ifstream&);
};
