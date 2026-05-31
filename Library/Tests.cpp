#include "Tests.hpp"
#include "doctest.h"

#include <sstream>
#include <iostream>
#include "User/Client.hpp"
#include "User/Admin.hpp"
#include "User/User.hpp"
#include "Utilities.hpp"
#include "Library&menu/Library.hpp"
#include "Library&menu/Menu.hpp"
#include "Book.hpp"

//TEST_CASE("check assert") {
//	ERROR(1 == 2);
//	CHECK(1 == 1);
//}

/// class User
TEST_CASE("User deserialize") {
	///
	///
	///
}

TEST_CASE("User getUsername") {
	Client c{"user", "pass"};
	CHECK(c.getUsername() == "user");
}

TEST_CASE("User getPassword") {
	Client c{ "user", "pass" };
	CHECK(c.getPassword() == "pass");
}

TEST_CASE("User isAdmin") {
	Client c{ "user", "pass" };
	CHECK_FALSE(c.isAdmin());

	Admin a{ "user", "pass" };
	CHECK(a.isAdmin());
}
/// class User


/// class Client
TEST_CASE("Client param constructor") {
	Client c{ "user", "pass" };
	CHECK(c.getUsername() == "user");
	CHECK(c.getPassword() == "pass");
}

TEST_CASE("Client serialize") {
	///
	///
	///
}

TEST_CASE("Client deserialize") {
	///
	///
	///
}
/// class Client


/// class Admin
TEST_CASE("Admin param constructor") {
	Admin a{ "user", "pass" };
	CHECK(a.getUsername() == "user");
	CHECK(a.getPassword() == "pass");
}

TEST_CASE("Admin deserialize") {
	///
	///
	///
}
/// class Admin


/// class Book
TEST_CASE("Book param constructor") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1", "tag2"}, 4.5, 12345 };
	CHECK(b.getAuthor() == "Author");
	CHECK(b.getTitle() == "Title");
	CHECK(b.getGenre() == "Genre");
	CHECK(b.getYear() == 2020);
	CHECK(b.getRating() == 4.5);
	CHECK(b.getTags().size() == 2);
	CHECK(b.getTags()[0] == std::string{ "tag1" });
	CHECK(b.getTags()[1] == std::string{ "tag2" });
	CHECK(b.getISBN() == 12345);
}

TEST_CASE("Book move constructor") {
	///
	///
	///
}

TEST_CASE("Book move assignment") {
	///
	///
	///
}

TEST_CASE("Book destructor") {
	///
	///
	///
}

TEST_CASE("Book serialize") {
	///
	///
	///
}

TEST_CASE("Book deserialize") {
	///
	///
	///
}

TEST_CASE("Book print") {
	///
	///
	///
}

TEST_CASE("Book getTitle") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1"}, 4.5, 12345 };
	CHECK(b.getTitle() == "Title");
}

TEST_CASE("Book getGenre") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1"}, 4.5, 12345 };
	CHECK(b.getGenre() == "Genre");
}

TEST_CASE("Book getAuthor") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1"}, 4.5, 12345 };
	CHECK(b.getAuthor() == "Author");
}

TEST_CASE("Book getYear") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1"}, 4.5, 12345 };
	CHECK(b.getYear() == 2020);
}

TEST_CASE("Book getRating") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1"}, 4.5, 12345 };
	CHECK(b.getRating() == 4.5);
}

TEST_CASE("Book getTags") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1"}, 4.5, 12345 };
	CHECK(b.getTags().size() == 1);
	CHECK(b.getTags()[0] == std::string{ "tag1" });
}

TEST_CASE("Book getISBN") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1"}, 4.5, 12345 };
	CHECK(b.getISBN() == 12345);
}

TEST_CASE("Book optionToString") {
	CHECK(Book::optionToString(BookOption::AUTHOR) == "author");
	CHECK(Book::optionToString(BookOption::TITLE) == "title");
	CHECK(Book::optionToString(BookOption::YEAR) == "year");
	CHECK(Book::optionToString(BookOption::RATING) == "rating");
}

TEST_CASE("Book stringToOption") {
	CHECK(Book::stringToOption("author") == BookOption::AUTHOR);
	CHECK(Book::stringToOption("title") == BookOption::TITLE);
	CHECK(Book::stringToOption("year") == BookOption::YEAR);
	CHECK(Book::stringToOption("rating") == BookOption::RATING);
}
/// class Book


/// namespace Utilities
TEST_CASE("Utilities checkIfOpen ifstream") {
	///
	///
	///
}

TEST_CASE("Utilities checkIfOpen ofstream") {
	///
	///
	///
}

TEST_CASE("Utilities checkIfExists") {
	///
	///
	///
}

TEST_CASE("Utilities logAndThrow") {
	///
	///
	///
}

TEST_CASE("Utilities skipLines") {
	///
	///
	///
}

TEST_CASE("Utilities clearCin") {
	///
	///
	///
}

TEST_CASE("Utilities to_lowercase") {
	///
	///
	///
}

TEST_CASE("Utilities stripWhitespaceFrontAndBack") {
	///
	///
	///
}

TEST_CASE("Utilities containsChar") {
	///
	///
	///
}
/// namespace Utilities


/// class Library
TEST_CASE("Library getLogLevel") {
	Library lib;
	REQUIRE(lib.getLogLevel() == Logging::VERBOSE);
}

TEST_CASE("Library destructor") {
	///
	///
	///
}

TEST_CASE("Library open") {
	///
	///
	///
}

TEST_CASE("Library close") {
	///
	///
	///
}

TEST_CASE("Library save") {
	///
	///
	///
}

TEST_CASE("Library saveas") {
	///
	///
	///
}

TEST_CASE("Library login") {
	///
	///
	///
}

TEST_CASE("Library logout") {
	///
	///
	///
}

TEST_CASE("Library usersAdd") {
	///
	///
	///
}

TEST_CASE("Library usersRemove") {
	///
	///
	///
}

TEST_CASE("Library booksAdd") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	Book* b{ new Book{ "Author", "Title", "Genre", "Description", 2020, {"tag1"}, 4.5, 12345 } };
	CHECK_NOTHROW(lib.booksAdd(b));

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library booksRemove") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.booksRemove(12345));

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library booksAll") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.booksAll());

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library booksInfo") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.booksInfo(99999));

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library booksFind") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.booksFind(BookOption::TITLE, "ABc"));
	CHECK(output.str() == "Couldn't find book with title abc.\n");
	output.str("");
	output.clear();

	CHECK_NOTHROW(lib.booksFind(BookOption::AUTHOR, "ABc"));
	CHECK(output.str() == "Couldn't find book with author abc.\n");
	output.str("");
	output.clear();
	
	CHECK_NOTHROW(lib.booksFind(BookOption::TAG, "ABc"));
	CHECK(output.str() == "Couldn't find book with tag abc.\n");
	output.str("");
	output.clear();

	CHECK_NOTHROW(lib.booksFind(BookOption::INVALID, "ABc"));
	CHECK(output.str() == "Option can only be title, author, or tag.\n");
	output.str("");
	output.clear();

	//Book* b{ new Book{ "Author", "Title", "Genre", "Description", 2020, {"tag1"}, 4.5, 12345 } };
	//lib.booksAdd(b);
	//CHECK_NOTHROW(lib.booksFind(BookOption::TITLE, "Title"));
	//std::stringstream book_print;
	//std::cout.rdbuf(book_print.rdbuf());
	//b->print();
	//std::cout << book_print.str();
	//CHECK(output.str() == book_print.str());

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library booksSort") {
	///
	///
	///
}

TEST_CASE("Library loggedIn") {
	Library lib;
	CHECK_FALSE(lib.loggedIn());
}

TEST_CASE("Library loggedInAsAdmin") {
	Library lib;
	CHECK_FALSE(lib.loggedInAsAdmin());
}

TEST_CASE("Library activeFile") {
	Library lib;
	CHECK_FALSE(lib.activeFile());
}

TEST_CASE("Library sortToString") {
	CHECK(Library::sortToString(BookSort::ASCENDING) == "ascending");
	CHECK(Library::sortToString(BookSort::DESCENDING) == "descending");
	CHECK(Library::sortToString(BookSort::INVALID) == "");
}

TEST_CASE("Library stringToSort") {
	CHECK(Library::stringToSort("asc") == BookSort::ASCENDING);
	CHECK(Library::stringToSort("ascending") == BookSort::ASCENDING);
	CHECK(Library::stringToSort("desc") == BookSort::DESCENDING);
	CHECK(Library::stringToSort("descending") == BookSort::DESCENDING);
	CHECK(Library::stringToSort("sdhfklsdhfksd") == BookSort::INVALID);
}
/// class Library


/// class Menu
TEST_CASE("Menu getInstance") {
	Menu& menu_1{ Menu::getInstance() };
	Menu& menu_2{ Menu::getInstance() };
	CHECK(&menu_1 == &menu_2);
}

TEST_CASE("Menu menu" * doctest::skip(false)) {
	Library lib;

	std::streambuf* cin_original{ std::cin.rdbuf() };
	std::stringstream input{ "exit\n" };
	std::cin.rdbuf(input.rdbuf());
	
	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());
	
	CHECK_NOTHROW(Menu::getInstance().menu(lib));
	
	std::cin.rdbuf(cin_original);
	std::cout.rdbuf(cout_original);

#ifdef AUTO_OPEN_LIBRARY_DAT
	FAIL_CHECK("Disable AUTO_OPEN_LIBRARY_DAT in Menu.hpp to test menu");
#endif
#ifdef AUTO_LOGIN_JOHN_PORK
	FAIL_CHECK("Disable AUTO_LOGIN_JOHN_PORK in Menu.hpp to test menu");
#endif

	CHECK(output.str() == "> Exiting the program...\n");
}
/// class Menu