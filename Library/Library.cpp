#include <string>
#include "Library.hpp"

Library::Library() : m_active_user() { m_users.push_back(new Admin{"admin", "i<3c++"}); }

void Library::free() {
	for (const User* u : m_users) {
		delete u;
	}

	for (const Book* b : m_books) {
		delete b;
	}

	m_active_user = "";
}

void Library::serialize() const {

}

void Library::deserialize() {

}

void Library::login() {

}

void Library::logout() {
	m_active_user = "";
}

void Library::usersAdd(User* user) {
	///check if user exists
	///
	///
}

void Library::usersRemove(std::string username) {

}

void Library::booksAll() const {

}

void Library::booksInfo(unsigned) const {

}

void Library::booksFind() const {

}

void Library::booksSort() {

}