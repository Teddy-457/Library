#include <iostream>
#include <string>
#include "Menu.hpp"
#include "../User/User.hpp"
#include "../User/Client.hpp"
#include "../User/Admin.hpp"
#include "../Utilities.hpp"

namespace {
    bool checkLoginAndLog(Library& library) {
        if (!library.loggedIn()) {
            std::cout << "You need to log in to run this command.\n";
            return false;
        }
        return true;
    }

    bool checkAdminAndLog(Library& library) {
        if (!library.loggedInAsAdmin()) {
            std::cout << "You need to be logged in as an administrator to run this command.\n";
            return false;
        }
        return true;
    }

    bool checkFileAndLog(Library& library) {
        if (!library.activeFile()) {
            std::cout << "You need to open a file to use this command.\n";
            return false;
        }
        return true;
    }
}

void Menu::menu(Library& library) {
    bool first_run{ true };
    while (true) {
        if (!first_run) {
            std::cout << '\n';
            first_run = false;
        }

        std::cout << "> ";
        std::string command;
        std::cin >> command;

        if (command == "open") {
            std::string filename;
            std::cin >> filename;
            ///
            ///error handling
            ///
            library.open(filename);
        }
        else if (command == "close") {
            library.close();
        }
        else if (command == "save") {
            library.save();
        }
        else if (command == "saveas") {
            std::string filename;
            std::cin >> filename;
            ///
            ///error handling
            ///
            library.saveas(filename);
        }
        else if (command == "help") {
            std::cout << "The following commands are supported:\n"
                "open <file>				opens <file>\n"
                "close					closes currently opened file\n"
                "save					saves the currently open file\n"
                "saveas <file>				saves the currently open file in <file>\n"
                "help					prints this information\n"
                "exit					exists the program\n\n"
                "login <username> <password>		logs in as <username>\n"
                "logout					logs out current user\n\n"
                "books all				prints information about all books\n"
                "      info/view <isbn_value>		prints detailed information about a book\n"
                "      find <option> <option_string> 	<option> can be title, author, or tag\n"
                "      sort <option> [asc | desc] 	<option> can be title, author, or tag\n"
                "      add <title> <author> <genre> 	adds book\n"
                "      <description> <year> <rating>\n"
                "      <isbn> <tags>\n"
                "      remove <isbn_value>	  	removes book with <isbn_value>\n\n"
                "users add <user> <password> <admin>	adds user (admin if argument set to 1)  \n"
                "      remove <user>			removes user <username>\n";
        }
        else if (command == "exit") {
            std::cout << "Exiting the program...\n";
            return;
        }
        else if (command == "login") {
            if (!checkFileAndLog(library)) { Utilities::clearCin(); continue; }

            if (library.loggedIn()) {
                std::cout << "You are already logged in.\n";
                Utilities::clearCin();
                continue;
            }

            ///
            ///при въвеждане на паролата на екрана да се изписва символа * вместо реалния символ
            ///

            std::string username;
            std::string password;
            std::cout << "Enter your username: ";
            std::cin >> username;
            std::cout << "Enter your password: ";
            std::cin >> password;
            ///
            ///error handling
            ///

            library.login(username, password);
        }
        else if (command == "logout") {
            if (!checkFileAndLog(library) || !checkLoginAndLog(library)) { continue; }

            library.logout();
        }
        else if (command == "books") {
            if (!checkFileAndLog(library) || !checkLoginAndLog(library)) {
                Utilities::clearCin();
                continue;
            }

            std::cin >> command;
            if (command == "all") {
                library.booksAll();
            }
            else if (command == "info" || command == "view") {
                unsigned long isbn;
                std::cin >> isbn;
                ///
                ///error handling
                ///

                library.booksInfo(isbn);
                std::cout << '\n';
            }
            else if (command == "find") {
                ///
                ///
                ///
            }
            else if (command == "sort") {
                ///
                ///
                ///
            }
            else if (command == "add") {
                if (!checkAdminAndLog(library)) { Utilities::clearCin(); continue; }

                ///
                ///
                ///
            }
            else if (command == "remove") {
                if (!checkAdminAndLog(library)) { Utilities::clearCin(); continue; }

                unsigned long isbn;
                std::cin >> isbn;
                ///
                ///error handling
                ///

                library.booksRemove(isbn);
            }
            else {
                std::cout << "Unknown command.\n";
            }
        }
        else if (command == "users") {
            if (!checkFileAndLog(library) || !checkAdminAndLog(library)) {
                Utilities::clearCin();
                continue;
            }

            std::cin >> command;
            if (command == "add") {
                std::string username;
                std::string password;
                bool admin;
                std::cin >> username >> password >> admin;
                ///
                ///error handling
                ///

                User* user;
                if (admin) {
                    user = new Admin{ username, password };
                }
                else {
                    user = new Client(username, password);
                }
                library.usersAdd(user);
            }
            else if (command == "remove") {
                std::string username;
                std::cin >> username;
                ///
                ///error handling
                ///

                library.usersRemove(username);
            }
            else {
                std::cout << "Unknown command.\n";
            }
        }
        else {
            std::cout << "Unknown command.\n";
        }
    }
}
