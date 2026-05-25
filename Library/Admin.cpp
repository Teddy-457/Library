#include <fstream>
#include "Admin.hpp"

Admin* Admin::deserialize(std::ifstream& file) {
    file.ignore(1);


    file.close();
    return new Admin;///
}

void Admin::booksAdd() const {

}

void Admin::booksRemove() const {

}

void Admin::usersAdd() const {

}

void Admin::usersRemove() const {
    
}