#include "Library.hpp"
#include <functional>
#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include "../Utilities.hpp"
#include "../Book.hpp"

Library::Library() : m_filename(""), m_active_user(""), m_admin_logged_in(false) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::Library()\n"; }
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

	bool file_exists{ Utilities::checkIfExists(filename) };

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

	std::string filename{ m_filename };
	free();
	std::cout << "Successfully closed " << filename << ".\n";
}

void Library::save() const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::save()\n"; }

	if (saveas(m_filename, true)) {
		std::cout << "Successfully saved " << m_filename << ".\n";
	}
}

bool Library::saveas(const std::string& filename, bool called_from_save) const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::saveas(" << filename << ")\n"; }

	if (m_filename == "") {
		std::cout << "You don't have an opened file.\n";
		return false;
	}

	serialize(filename);
	if (!called_from_save) { std::cout << "Successfully saved another " << filename << ".\n"; }
	return true;
}

void Library::serialize(const std::string& filename) const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::serialize(" << filename << ")\n"; }

    std::ofstream file(filename, std::ios::out);
    Utilities::checkIfOpen(file);

	file << m_users.size() << '\n'; file.close();
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
		User* user{ User::deserialize(filename, i) };
		m_users.push_back(user);
	}

	file.open(filename, std::ios::in);
	Utilities::checkIfOpen(file);

	Utilities::skipLines(file, users + 1);
	int books; file >> books; file.close();
	for (int i = users + 2; i <= books + users + 1; ++i) {
		Book* book{ Book::deserialize(filename, i) };
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
	if (m_LOG_LEVEL != Logging::QUIET) { std::cout << "Logged out.\n"; }
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

Logging Library::getLogLevel() const {
	return m_LOG_LEVEL;
}

void Library::usersAdd(User* user) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::usersAdd(User*)\n"; }

	std::string username{ user->getUsername() };
	if (username == "admin") { return; }
	for (const User* u : m_users) {
		if(u->getUsername() == username) {
			std::cout << "A user with that username already exists.\n";
			delete user;
			return;
		}
	}
	m_users.push_back(user);
	if(user->isAdmin()) {
		if (m_LOG_LEVEL != Logging::QUIET) { std::cout << "Added admin " << username << '.' << '\n'; }
	}
	else {
		if (m_LOG_LEVEL != Logging::QUIET) { std::cout << "Added user " << username << '.' << '\n'; }
	}
}

void Library::usersRemove(const std::string& username) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::usersRemove(" << username << ")\n"; }

	if (username == "admin") {
		std::cout << "Can't delete default admin user.\n";
		return;
	}

	for (int i = 0; i < m_users.size(); ++i) {
		if(m_users[i]->getUsername() == username) {
			delete m_users[i];
			m_users.erase(m_users.begin() + i);
			if (m_active_user == username) { logout(); }
			if (m_LOG_LEVEL != Logging::QUIET) { std::cout << "Deleted user " << username << '.' << '\n'; }
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
			delete book;
			return;
		}
	}
	m_books.push_back(book);
	if (m_LOG_LEVEL != Logging::QUIET) { std::cout << "Added " << book->getTitle() << ".\n"; }
}

void Library::booksRemove(unsigned long isbn) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksRemove(" << isbn << ")\n"; }

	for (int i = 0; i < m_books.size(); ++i) {
		if(m_books[i]->getISBN() == isbn) {
			if (m_LOG_LEVEL != Logging::QUIET) { std::cout << "Removed " << m_books[i]->getTitle() << ".\n"; }
			delete m_books[i];
			m_books.erase(m_books.begin() + i);
			return;
		}
	}
	std::cout << "No book with that isbn exists.\n";
}

void Library::booksAll() const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksAll()\n"; }

	for(const Book* b : m_books) {
		std::cout << "Title: " <<  b->getTitle() << '\n'
				  << "Author: " << b->getAuthor() << '\n'
				  << "Genre: " << b->getGenre() << '\n'
				  << "ISBN: " << b->getISBN() << "\n\n";
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
	std::cout << "No book with that ISBN exists.\n";
}

void Library::booksFind(BookOption option, std::string option_string) const {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksFind(Book::Option, " << option_string << ")\n"; }

	option_string = Utilities::to_lowercase(option_string);
	
	bool found{ false };
	switch (option) {
		case BookOption::TITLE:
			found = findBookByTitle(option_string);
			break;
		case BookOption::AUTHOR:
			found = findBookByAuthor(option_string);
			break;
		case BookOption::TAG:
			found = findBookByTag(option_string);
			break;
		default:
			std::cout << "Option can only be title, author, or tag.\n";
			return;
	}
	if (!found) { std::cout << "Couldn't find book with " 
		<< Book::optionToString(option) << ' ' << option_string << ".\n";
	}
}

bool Library::findBookByTitle(const std::string& title) const {
	for (const Book* b : m_books) {
		if (Utilities::to_lowercase(b->getTitle()) == title) {
			b->print();
			return true;
		}
	}
	return false;
}

bool Library::findBookByAuthor(const std::string& author) const {
	for (const Book* b : m_books) {
		if (Utilities::to_lowercase(b->getAuthor()) == author) {
			b->print();
			return true;
		}
	}
	return false;
}

bool Library::findBookByTag(const std::string& tag) const {
	for (const Book* b : m_books) {
		for (const char* t : b->getTags()) {
			if (Utilities::to_lowercase(t) == tag) {
				b->print();
				return true;
			}
		}
	}
	return false;
}

std::string Library::sortToString(BookSort option) {
	switch (option) {
		case BookSort::ASCENDING:
			return "ascending";
		case BookSort::DESCENDING:
			return "descending";
		case BookSort::INVALID:
			return "";
		default:
			Utilities::logAndThrow("No such BookSort exists");
	}
}

BookSort Library::stringToSort(const std::string& option) {
	if (option == "asc" || option == "ascending") {
		return BookSort::ASCENDING;
	}
	else if (option == "desc" || option == "descending") {
		return BookSort::DESCENDING;
	}
	else {
		return BookSort::INVALID;
	}
}

void Library::booksSort(BookOption option, BookSort sort) {
	if (m_LOG_LEVEL == Logging::DEBUG) { std::cout << "Library::booksSort(Book::Option, Library::Sort)\n"; }

	using SortFun = std::function<bool(const Book*, const Book*)>;

	if (sort == BookSort::INVALID) {
		std::cout << "Invalid sorting type [asc | desc].\n";
		return;
	}

	SortFun sorting_option;
	switch (option) {
		case BookOption::TITLE:
			sorting_option = [](const Book* b_1, const Book* b_2)->bool
				{ return b_1->getTitle() > b_2->getTitle(); };
			break;
		case BookOption::AUTHOR:
			sorting_option = [](const Book* b_1, const Book* b_2)->bool
				{ return b_1->getAuthor() > b_2->getAuthor(); };
			break;
		case BookOption::YEAR:
			sorting_option = [](const Book* b_1, const Book* b_2)->bool
				{ return b_1->getYear() > b_2->getYear(); };
			break;
		case BookOption::RATING:
			sorting_option = [](const Book* b_1, const Book* b_2)->bool
				{ return b_1->getRating() > b_2->getRating(); };
			break;
		default:
			std::cout << "Option can only be title, author, year, or rating.\n";
			return;
	}

	if (sort == BookSort::DESCENDING) {
		SortFun copy{ sorting_option };
		sorting_option = [copy](const Book* b_1, const Book* b_2)->bool
			{ return copy(b_2, b_1); };
	}

	auto insertionSort = [this](SortFun sorting_option) -> void {
		for (std::size_t i = 1; i < m_books.size(); ++i) {
			Book* book{ std::move(m_books[i]) };

			std::size_t j{ i };
			while (j > 0 && sorting_option(m_books[j - 1], book)) {
				m_books[j] = m_books[j - 1];
				--j;
			}

			m_books[j] = std::move(book);
		}
	};

	insertionSort(sorting_option);
	std::cout << "Sorted " << m_books.size() << " books by "
		<< Book::optionToString(option) << " in " << sortToString(sort) << " order.\n";
};