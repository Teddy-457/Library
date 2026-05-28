#include <string>
#include <fstream>
#include <iostream>
#include "Library.hpp"
#include "../Utilities.hpp"

Library::Library() : m_filename(""), m_active_user(""), m_admin_logged_in(false) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::Library()\n"; }

	m_users.push_back(new Admin{"admin", m_default_admin_password});
}

void Library::free() {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::free()\n"; }

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
	m_users.push_back(new Admin{"admin", m_default_admin_password});
}

Library::~Library() {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::~Library()\n"; }

	free();
}

void Library::open(const std::string& filename) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::open(" << filename << ")\n"; }

	if(m_filename != "") {
		std::cout << "You need to close the currently opened file first.\n";
		return;
	}

	bool file_exists{Utilities::checkIfExists(filename)};

	if(file_exists) {
		deserialize(filename);
		std::cout << "Successfully opened " << filename << ".\n";
	}
	else {
		std::ofstream file(filename, std::ios::out); file.close();
		free();
		m_filename = filename;
		std::cout << "Successfully (created and) opened " << filename << ".\n";
	}
}

void Library::close() {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::close()\n"; }

	if (m_filename == "") {
		std::cout << "No file is opened.\n";
		return;
	}

	std::string filename{m_filename};
	free(); ///could this free be a problem?
	std::cout << "Successfully closed " << filename << ".\n";
}

void Library::save() const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::save()\n"; }

	saveas(m_filename, true);
	std::cout << "Successfully saved " << m_filename << ".\n";
    ///
	///
	///
}

void Library::saveas(const std::string& filename, bool called_from_save) const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::saveas(" << filename << ")\n"; }

	if (m_filename == "") {
		std::cout << "You don't have an opened file.\n";
		return;
	}

	serialize(filename);
	if (!called_from_save) { std::cout << "Successfully saved another" << filename << ".\n"; }
    ///
	///
	///
}

void Library::serialize(const std::string& filename) const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::serialize(" << filename << ")\n"; }

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
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::deserialize(" << filename << ")\n"; }

	free();
	m_filename = filename;
	
	std::ifstream file(filename, std::ios::in);
    Utilities::checkIfOpen(file);

	if (file.peek() == std::ifstream::traits_type::eof()) { file.close(); return; } //check for empty file generated with open()

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
		Book* book = Book::deserialize(filename, i);
		m_books.push_back(book);
	}
}

void Library::login(const std::string& username, const std::string& password) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::login(" << username << ", " << password << ")\n"; }

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
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::logout()\n"; }

	m_active_user = "";
	m_admin_logged_in = false;
	if (m_LOG_LEVEL == Logging::VERBOSE) { std::cout << "Logged out.\n"; }
}

bool Library::loggedIn() const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::loggedIn()\n"; }

	return m_active_user != "";
}

bool Library::loggedInAsAdmin() const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::loggedInAsAdmin()\n"; }

	return m_admin_logged_in;
}

bool Library::activeFile() const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::activeFile()\n"; }

	return m_filename != "";
}

void Library::usersAdd(User* user) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::usersAdd(User*)\n"; }

	std::string username{user->getUsername()};
	for (const User* u : m_users) {
		if(u->getUsername() == username) {
			std::cout << "A user with that username already exists.\n";
			return;
		}
	}
	m_users.push_back(user);
	if(user->isAdmin()) {
		if (m_LOG_LEVEL == Logging::VERBOSE) { std::cout << "Added admin " << username << '.' << '\n'; }
	}
	else {
		if (m_LOG_LEVEL == Logging::VERBOSE) { std::cout << "Added user " << username << '.' << '\n'; }
	}
}

void Library::usersRemove(const std::string& username) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::usersRemove(" << username << ")\n"; }

	if(username=="admin") {
		std::cout << "Can't delete default admin user.\n";
		return;
	}

	for (int i = 0; i < m_users.size(); ++i) {
		if(m_users[i]->getUsername() == username) {
			m_users.erase(m_users.begin() + i);
			if (m_active_user == username) { logout(); }
			if (m_LOG_LEVEL == Logging::VERBOSE) { std::cout << "Deleted user " << username << '.' << '\n'; }
			return;
		}
	}
	std::cout << "No user with that username exists.\n";
}

void Library::booksAdd(Book* book) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksAdd(Book*)\n"; }

	for (const Book* b : m_books) {
		if(b->getISBN() == book->getISBN()) {
			std::cout << "A book with that ISBN already exists.\n";
			return;
		}
	}
	m_books.push_back(book);
	if (m_LOG_LEVEL == Logging::VERBOSE) { std::cout << "Added " << book->getTitle() << ".\n"; }
}

void Library::booksRemove(unsigned long isbn) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksRemove(" << isbn << ")\n"; }

	for (int i = 0; i < m_books.size(); ++i) {
		if(m_books[i]->getISBN() == isbn) {
			if (m_LOG_LEVEL == Logging::VERBOSE) { std::cout << "Removed " << m_books[i]->getTitle() << ".\n"; }
			m_books.erase(m_books.begin() + i);
			return;
		}
	}
	std::cout << "No book with that isbn exists.\n";
}

void Library::booksAll() const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksAll()\n"; }

	for(const Book* b : m_books) {
		std::cout << b->getTitle() << '\n'
				  << b->getAuthor() << '\n'
				  << b->getGenre() << '\n'
				  << b->getISBN() << "\n\n";
	}
}

void Library::booksInfo(unsigned long isbn) const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksInfo(" << isbn << ")\n"; }

	for(const Book* b : m_books) {
		if (b->getISBN() == isbn) {
			b->print();
			return;
		}
	}
}

void Library::booksFind(const Book::Option& option, std::string option_string) const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksFind(Book::Option, " << option_string << ")\n"; }

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
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksSort(Book::Option, Library::Sort)\n"; }

	///при сортиране на книгите по зададен критерий, да се напише алгоритъм различен от пряка селекция и метода на мехурчето
	
	///
	///
	///
}