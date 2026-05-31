#include "Tests.hpp"
#include "doctest.h"

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
	CHECK(!c.isAdmin());

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
	///
	///
	///
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
	///
	///
	///
}

TEST_CASE("Book getGenre") {
	///
	///
	///
}

TEST_CASE("Book getAuthor") {
	///
	///
	///
}

TEST_CASE("Book getYear") {
	///
	///
	///
}

TEST_CASE("Book getRating") {
	///
	///
	///
}

TEST_CASE("Book getTags") {
	///
	///
	///
}

TEST_CASE("Book getISBN") {
	///
	///
	///
}

TEST_CASE("Book optionToString") {
	///
	///
	///
}

TEST_CASE("Book stringToOption") {
	///
	///
	///
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
	///
	///
	///
}

TEST_CASE("Library booksRemove") {
	///
	///
	///
}

TEST_CASE("Library booksAll") {
	///
	///
	///
}

TEST_CASE("Library booksInfo") {
	///
	///
	///
}

TEST_CASE("Library booksFind") {
	///
	///
	///
}

TEST_CASE("Library booksSort") {
	///
	///
	///
}

TEST_CASE("Library loggedIn") {
	///
	///
	///
}

TEST_CASE("Library loggedInAsAdmin") {
	///
	///
	///
}

TEST_CASE("Library activeFile") {
	///
	///
	///
}

TEST_CASE("Library getLogLevel") {
	///
	///
	///
}

TEST_CASE("Library sortToString") {
	///
	///
	///
}

TEST_CASE("Library stringToSort") {
	///
	///
	///
}
/// class Library


/// class Menu
TEST_CASE("Menu getInstance") {
	///
	///
	///
}

TEST_CASE("Menu menu") {
	///
	///
	///
}
/// class Menu