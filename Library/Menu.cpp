#include <iostream>
#include <string>
#include "Menu.hpp"
#include "Utilities.hpp"

void Menu::menu(Library& library) {
    bool first_run{ true };
    while (true) {
        if (!first_run) {
            std::cout << '\n';
            first_run = false;
        }
        std::string command;
        std::cout << "> ";
        std::cin >> command;

        if (command == "open") {
            ///
            ///
            ///
        }
        else if (command == "close") {
            ///
            ///
            ///
        }
        else if (command == "save") {
            ///
            ///
            ///
        }
        else if (command == "saveas") {
            ///
            ///
            ///
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
            if (library.loggedIn()) {
                std::cout << "You are already logged in.\n";
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
        if (!library.loggedIn()) {
            std::cout << "You need to be logged in to use this command / the command doesn't exist\n";
            Utilities::clearCin();
        }
        else if (command == "logout") {
            library.logout();
        }
        else if (command == "books") {
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
                if (!library.loggedInAsAdmin()) {
                    std::cout << "You need to be logged in as an administrator to run this command.\n";
                    continue;
                }

                ///
                ///
                ///
            }
            else if (command == "remove") {
                if (!library.loggedInAsAdmin()) {
                    std::cout << "You need to be logged in as an administrator to run this command.\n";
                    continue;
                }

                unsigned long isbn;
                std::cin >> isbn;
                ///
                ///error handling
                ///

                library.booksRemove(isbn);
            }
            //else {
            //    std::cout << "Command doesn't exist.1\n";
            //}
        }
        else if (command == "users") {
            std::cin >> command;
            if (command == "add") {
                if (!library.loggedInAsAdmin()) {
                    std::cout << "You need to be logged in as an administrator to run this command.\n";
                    continue;
                }

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
                if (!library.loggedInAsAdmin()) {
                    std::cout << "You need to be logged in as an administrator to run this command.\n";
                    continue;
                }

                std::string username;
                std::cin >> username;
                ///
                ///error handling
                ///

                library.usersRemove(username);
            }
            //else {
            //    std::cout << "Command doesn't exist2.\n";
            //}
        }
        //else {
        //    std::cout << "Command doesn't exist3.\n";
        //}
    }
}
