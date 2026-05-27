#include <string>
#include <fstream>
#include <iostream>
#include "Library.hpp"
#include "Utilities.hpp"

Library::Library() : m_filename(""), m_active_user(""), m_admin_logged_in(false) { m_users.push_back(new Admin{"admin", m_default_admin_password}); }

void Library::free() {
	for (const User* u : m_users) {
		delete u;
	}
	m_users.clear();
	for (const Book* b : m_books) {
		delete b;
	}
	m_books.clear();

	m_filename = "";
	m_active_user = "";
	m_admin_logged_in = false;
}

Library::~Library() {
	free();
}

void Library::open() {
    ///
}

void Library::close() {
    ///
}

void Library::save() {
    ///
}

void Library::saveas() {
    ///
}

void Library::serialize(const std::string& filename) const {
    std::ofstream file(filename, std::ios::out);
    Utilities::checkIfOpen(file);

	file << m_users.size() - 1 << '\n'; file.close(); //default admin user doesn't exist in the file (-1)
	for(const User* u : m_users) {
		u->serialize(filename);
	}
	
	file.open(filename, std::ios::app);
    Utilities::checkIfOpen(file);

	file << m_books.size() << '\n'; file.close();
	for(const Book* b : m_books) {
		b->serialize(filename);
	}
}

void Library::deserialize(const std::string& filename) {
	free();
	m_users.push_back(new Admin{"admin", m_default_admin_password});

	std::ifstream file(filename, std::ios::in);
    Utilities::checkIfOpen(file);

	int users; file >> users; file.close();
	for (int i = 1; i <= users; ++i) {
		User* user = User::deserialize(filename, i);
		m_users.push_back(user);
	}

	file.open(filename, std::ios::in);
	Utilities::checkIfOpen(file);

	Utilities::skipLines(file, users+1);
	int books; file >> books; file.close();
	for (int i = users + 2; i <= books + users + 1; ++i) {
		std::cout << i << '\n';
		Book* book = Book::deserialize(filename, i);
		m_books.push_back(book);
	}
}

void Library::login() {
	///при въвеждане на паролата на екрана да се изписва символа * вместо реалния символ
	
	if(m_active_user != "") {
		std::cout << "You are already logged in.\n";
		return;
	}

	std::string username;
	std::string password;
	std::cout << "Enter your username: ";
	std::cin >> username;
	///error handling
	std::cout << "Enter your password: ";
	std::cin >> password;
	///error handling

	if(username == "admin") {
		if(password == m_default_admin_password) {
			m_active_user = "admin";
			m_admin_logged_in = true;
			std::cout << "Welcome, admin!\n";
			return;
		}
		std::cout << "Wrong username/password.\n";
		return;
	}

	for(const User* u : m_users) {
		if(u->getUsername() == username) {
			if(password == u->getPassword()) {
				m_active_user = username;
				m_admin_logged_in = u->isAdmin();
				std::cout << "Welcome, " << username <<"!\n";
				return;
			}
		}
	}
	std::cout << "Wrong username/password.\n";
}

void Library::logout() {
	if(m_active_user == "") {
		std::cout << "You are already logged out.\n";
		return;
	}

	m_active_user = "";
	m_admin_logged_in = false;
	std::cout << "Logged out.\n";
}

//bool Library::loggedIn() const {
//	return m_active_user != "";
//}
//
//bool Library::loggedInAsAdmin() const {
//	return m_admin_logged_in;
//}

void Library::usersAdd(User* user) {
	std::string username{user->getUsername()};
	for (const User* u : m_users) {
		if(u->getUsername() == username) {
			std::cout << "A user with that username already exists.\n";
			return;
		}
	}
	m_users.push_back(user);
	if(user->isAdmin()) {
		std::cout << "Added admin " << username << '.' << '\n';
	}
	else {
		std::cout << "Added user " << username << '.' << '\n';
	}
}

void Library::usersRemove(const std::string& username) {
	if(username=="admin") {
		std::cout << "Can't delete default admin user.\n";
		return;
	}

	for (int i = 0; i < m_users.size(); ++i) {
		if(m_users[i]->getUsername() == username) {
			m_users.erase(m_users.begin() + i);
			std::cout << "Deleted user " << username << '.' << '\n';
			return;
		}
	}
	std::cout << "No user with that username exists.\n";
}

void Library::booksAdd(Book* book) {
	for (const Book* b : m_books) {
		if(b->getISBN() == book->getISBN()) {
			std::cout << "A book with that ISBN already exists.\n";
			return;
		}
	}
	m_books.push_back(book);
	std::cout << "Added " << book->getTitle() << ".\n";
}

void Library::booksRemove(unsigned long isbn) {
	for (int i = 0; i < m_books.size(); ++i) {
		if(m_books[i]->getISBN() == isbn) {
			std::cout << "Removed " << m_books[i]->getTitle() << ".\n";
			m_books.erase(m_books.begin() + i);
			return;
		}
	}
	std::cout << "No book with that isbn exists.\n";
}

void Library::booksAll() const {
	for(const Book* b : m_books) {
		std::cout << b->getTitle() << '\n'
				  << b->getAuthor() << '\n'
				  << b->getGenre() << '\n'
				  << b->getISBN() << "\n\n";
	}
}

void Library::booksInfo(unsigned long isbn) const {
	for(const Book* b : m_books) {
		if (b->getISBN() == isbn) {
			b->print();
			return;
		}
	}
}

void Library::booksFind(const Book::Option& option, std::string option_string) const {
	///Търсене на книга по зададен критерий да игнорира регистъра на буквите (малки или големи)
	
	auto to_lowercase = [](std::string &str) -> void {
		for (char& c : str) { c = std::tolower(c); }
	};
	to_lowercase(option_string);
	
	///
	///
	///
}

enum class Library::Sort {
	ASCENDING,
	DESCENDING,
};

void Library::booksSort(const Book::Option&, const Sort& sort) {
	///при сортиране на книгите по зададен критерий, да се напише алгоритъм различен от пряка селекция и метода на мехурчето
	
	///
	///
	///
}