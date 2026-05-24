#pragma once

#include "Client.hpp"

class Admin : public Client {
public:
    void virtual booksAdd() const override;
    void virtual booksRemove() const override;
    void virtual usersAdd() const override;
    void virtual usersRemove() const override;
};
