#include "Tests.hpp"
#include "doctest.h"

#include <sstream>
#include <iostream>
#include <cstdio>
#include <fstream>
#include "User/Client.hpp"
#include "User/Admin.hpp"
#include "User/User.hpp"
#include "Utilities.hpp"
#include "Library&menu/Library.hpp"
#include "Library&menu/Menu.hpp"
#include "Book.hpp"

/// class Client
TEST_CASE("Client param constructor") {
	Client c{ "user", "pass" };
	REQUIRE(c.getUsername() == "user");
	REQUIRE(c.getPassword() == "pass");
}

TEST_CASE("Client serialize") {
	Admin a{ "user", "pass" };
	CHECK_NOTHROW(a.serialize("temp_test_output"));
	
	Client c{ "user", "pass" };
	CHECK_NOTHROW(c.serialize("temp_test_output"));
}

TEST_CASE("Client deserialize") {
	User* c{ User::deserialize("temp_test_output", 0) };
	CHECK(c->getUsername() == "user");
	CHECK(c->getPassword() == "pass");
	delete c;
}
/// class Client


/// class Admin
TEST_CASE("Admin param constructor") {
	Admin a{ "user", "pass" };
	REQUIRE(a.getUsername() == "user");
	REQUIRE(a.getPassword() == "pass");
}

TEST_CASE("Admin deserialize") {
	User* a{ User::deserialize("temp_test_output", 0) };
	CHECK(a->getUsername() == "user");
	CHECK(a->getPassword() == "pass");
	delete a;
}
/// class Admin


/// class User
TEST_CASE("User deserialize") {
	User* u{ User::deserialize("temp_test_output", 0) };
	REQUIRE(u != nullptr);
	CHECK(u->getUsername() == "user");
	CHECK(u->getPassword() == "pass");

	delete u;
}

TEST_CASE("Delete temp_test_output") {
	REQUIRE_FALSE(std::remove("temp_test_output"));
}

TEST_CASE("User getUsername") {
	Client c{ "user", "pass" };
	REQUIRE(c.getUsername() == "user");
}

TEST_CASE("User getPassword") {
	Client c{ "user", "pass" };
	REQUIRE(c.getPassword() == "pass");
}

TEST_CASE("User isAdmin") {
	Client c{ "user", "pass" };
	CHECK_FALSE(c.isAdmin());

	Admin a{ "user", "pass" };
	REQUIRE(a.isAdmin());
}
/// class User


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
	Book b1{ "Author", "Title", "Genre", "Description", 2020, {"tag1", "tag2"}, 4.5, 12345 };
	Book b2{ std::move(b1) };
	
	CHECK(b2.getAuthor() == "Author");
	CHECK(b2.getTitle() == "Title");
	CHECK(b2.getGenre() == "Genre");
	CHECK(b2.getYear() == 2020);
	CHECK(b2.getRating() == 4.5);
	CHECK(b2.getTags().size() == 2);
	CHECK(b2.getTags()[0] == std::string{ "tag1" });
	CHECK(b2.getTags()[1] == std::string{ "tag2" });
	CHECK(b2.getISBN() == 12345);
}

TEST_CASE("Book move assignment") {
	Book b1{ "Author", "Title", "Genre", "Description", 2020, {"tag1", "tag2"}, 4.5, 12345 };
	Book b2{ "", "", "", "", 0, {}, 0.0, 0 };
	b2 = std::move(b1);
	
	CHECK(b2.getAuthor() == "Author");
	CHECK(b2.getTitle() == "Title");
	CHECK(b2.getGenre() == "Genre");
	CHECK(b2.getYear() == 2020);
	CHECK(b2.getRating() == 4.5);
	CHECK(b2.getTags().size() == 2);
	CHECK(b2.getTags()[0] == std::string{ "tag1" });
	CHECK(b2.getTags()[1] == std::string{ "tag2" });
	CHECK(b2.getISBN() == 12345);
}

TEST_CASE("Book destructor") {
	Book* b{ new Book{ "Author", "Title", "Genre", "Description", 2020, {"tag1", "tag2"}, 4.5, 12345 } };
	CHECK_NOTHROW(delete b);
}

TEST_CASE("Book serialize") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1", "tag2"}, 4.5, 12345 };
	CHECK_NOTHROW(b.serialize("temp_test_output"));
}

TEST_CASE("Book deserialize") {
	Book* b{ Book::deserialize("temp_test_output", 0) };
	REQUIRE(b != nullptr);
	CHECK(b->getAuthor() == "Author");
	CHECK(b->getTitle() == "Title");
	CHECK(b->getGenre() == "Genre");
	CHECK(b->getYear() == 2020);
	CHECK(b->getRating() == 4.5);
	CHECK(b->getTags().size() == 2);
	CHECK(b->getTags()[0] == std::string{ "tag1" });
	CHECK(b->getTags()[1] == std::string{ "tag2" });
	CHECK(b->getISBN() == 12345);

	delete b;
}

TEST_CASE("Delete temp_test_output") {
	std::remove("temp_test_output");
}

TEST_CASE("Book print") {
	Book b{ "Author", "Title", "Genre", "Description", 2020, {"tag1", "tag2"}, 4.5, 12345 };
	
	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());
	
	CHECK_NOTHROW(b.print());
	CHECK_FALSE(output.str().empty());
	
	std::cout.rdbuf(cout_original);
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
	std::ofstream temp("temp_test", std::ios::out);
	temp << "test";
	temp.close();

	std::ifstream pass("temp_test", std::ios::in);
	CHECK_NOTHROW(Utilities::checkIfOpen(pass));
	pass.close();

	std::streambuf* cout_original{ std::cerr.rdbuf() };
	std::stringstream output;
	std::cerr.rdbuf(output.rdbuf());

	std::ifstream fail("doesntexist", std::ios::in);
	CHECK_THROWS(Utilities::checkIfOpen(fail));

	std::cerr.rdbuf(cout_original);
}

TEST_CASE("Utilities checkIfOpen ofstream") {
	std::ofstream pass("temp_test", std::ios::out);
	CHECK_NOTHROW(Utilities::checkIfOpen(pass));
	pass.close();

	std::remove("temp_test");
}

TEST_CASE("Utilities checkIfExists") {
	std::ofstream temp("temp_test", std::ios::out);
	temp << "test";
	temp.close();

	CHECK(Utilities::checkIfExists("temp_test"));

	std::remove("temp_test");

	CHECK_FALSE(Utilities::checkIfExists("temp_test"));
}

TEST_CASE("Utilities logAndThrow") {
	std::streambuf* cerr_original{ std::cerr.rdbuf() };
	std::stringstream output;
	std::cerr.rdbuf(output.rdbuf());

	CHECK_THROWS(Utilities::logAndThrow("Test error message"));
	CHECK_FALSE(output.str().empty());

	std::cerr.rdbuf(cerr_original);
}

TEST_CASE("Utilities skipLines") {
	std::ofstream temp("temp_test", std::ios::out);
	temp << "line1\nline2\nline3\n";
	temp.close();

	std::ifstream in("temp_test", std::ios::in);
	REQUIRE(in.is_open());

	CHECK_NOTHROW(Utilities::skipLines(in, 1));
	
	std::string line;
	std::getline(in, line);
	CHECK(line == "line2");

	in.close();
	std::remove("temp_test");
}

TEST_CASE("Utilities clearCin") {
	std::streambuf* cin_original{ std::cin.rdbuf() };
	std::stringstream input{ "test input\n" };
	std::cin.rdbuf(input.rdbuf());

	std::cin.setstate(std::ios::failbit);
	REQUIRE(std::cin.fail());

	CHECK_NOTHROW(Utilities::clearCin());
	CHECK_FALSE(std::cin.fail());

	std::cin.rdbuf(cin_original);
}

TEST_CASE("Utilities to_lowercase") {
	std::string test1 = "HELLO WORLD";
	CHECK(Utilities::to_lowercase(test1) == "hello world");

	std::string test2 = "hello world";
	CHECK(Utilities::to_lowercase(test2) == "hello world");
}

TEST_CASE("Utilities stripWhitespaceFrontAndBack") {
	std::string test1 = " hello world ";
	Utilities::stripWhitespaceFrontAndBack(test1);
	CHECK(test1 == "hello world");

	std::string test2 = "hello world";
	Utilities::stripWhitespaceFrontAndBack(test2);
	CHECK(test2 == "hello world");
}

TEST_CASE("Utilities containsChar") {
	CHECK(Utilities::containsChar("test string", 's'));
	CHECK_FALSE(Utilities::containsChar("test string", 'z'));
	CHECK_FALSE(Utilities::containsChar("", 'a'));
}
/// namespace Utilities


/// class Library
TEST_CASE("Library getLogLevel") {
	Library lib;
	REQUIRE(lib.getLogLevel() == Logging::VERBOSE);
}

TEST_CASE("Library destructor") {
	Library* lib{ new Library() };
	CHECK_NOTHROW(delete lib);
}

TEST_CASE("Library open") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.open("test_file"));

	std::cout.rdbuf(cout_original);
	std::remove("test_file");
}

TEST_CASE("Library close") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.close());

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library save") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.save());

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library saveas") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.saveas("smth"));

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library login") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.login("admin", "i<3c++"));

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library logout") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.logout());
	CHECK_FALSE(lib.loggedIn());

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library usersAdd") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	Client* c{ new Client{"user", "pass"}};
	CHECK_NOTHROW(lib.usersAdd(c));

	std::cout.rdbuf(cout_original);
}

TEST_CASE("Library usersRemove") {
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.usersRemove("user"));

	std::cout.rdbuf(cout_original);
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
	Library lib;

	std::streambuf* cout_original{ std::cout.rdbuf() };
	std::stringstream output;
	std::cout.rdbuf(output.rdbuf());

	CHECK_NOTHROW(lib.booksSort(BookOption::TITLE, BookSort::ASCENDING));
	CHECK_NOTHROW(lib.booksSort(BookOption::AUTHOR, BookSort::DESCENDING));
	CHECK_NOTHROW(lib.booksSort(BookOption::YEAR, BookSort::ASCENDING));
	CHECK_NOTHROW(lib.booksSort(BookOption::RATING, BookSort::DESCENDING));
	CHECK_NOTHROW(lib.booksSort(BookOption::INVALID, BookSort::INVALID));

	std::cout.rdbuf(cout_original);
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