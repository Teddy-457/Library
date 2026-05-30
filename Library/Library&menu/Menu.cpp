#include <iostream>
#include <string>
#include <conio.h>
#include "Menu.hpp"
#include "../User/User.hpp"
#include "../User/Client.hpp"
#include "../User/Admin.hpp"
#include "../Utilities.hpp"

#define AUTO_OPEN_LIBRARY_DAT
#define AUTO_LOGIN_JOHN_PORK

namespace { //or use static functions for internal linkage
    bool checkLoginAndLog(const Library& library) {
        if (!library.loggedIn()) {
            std::cout << "You need to log in to run this command.\n";
            return false;
        }
        return true;
    }

    bool checkAdminAndLog(const Library& library) {
        if (!library.loggedInAsAdmin()) {
            std::cout << "You need to be logged in as an administrator to run this command.\n";
            return false;
        }
        return true;
    }

    bool checkFileAndLog(const Library& library) {
        if (!library.activeFile()) {
            std::cout << "You need to open a file to use this command.\n";
            return false;
        }
        return true;
    }
}

Menu& Menu::getInstance() {
    static Menu menu;
    return menu;
}

void Menu::menu(Library& library) {
    bool first_run{ true };
    while (true) {
        static int run{ 0 };
        ++run;

#ifdef AUTO_OPEN_LIBRARY_DAT
        if (run == 1) {
            std::cout << "[AUTO_OPEN_LIBRARY_DAT] ";
            library.open("Library.dat");
            continue;
        }
#ifdef AUTO_LOGIN_JOHN_PORK
        else if (run == 2) {
            std::cout << "[AUTO_LOGIN_JOHN_PORK] ";
            library.login("john-pork", "1");
            continue;
        }
#endif
#endif

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
                "books all/list				prints information about all books\n"
                "      info/view <isbn_value>		prints detailed information about a book\n"
                "      find <option> <option_string> 	<option> can be title, author, or tag\n"
                "      sort <option> [asc | desc] 	<option> can be title, author, year or rating\n"
                "      add <title> <author> <genre> 	adds book, tags are comma separated\n"
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

            std::cout << "Enter your username: ";
            std::string username;
            std::cin >> username;

            std::cout << "Enter your password: ";
            std::string password;
            for (char c = _getch(); c != '\r'; c = _getch()) {
                if (c != '\b') {
                    password.push_back(c);
                    std::cout << '*';
                }
                else if (!password.empty()) {
                    std::cout << "\b \b";
                    password.pop_back();
                }
            }
            std::cout << '\n';
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
            if (command == "all" || command == "list") {
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
                std::string option;
                std::cin >> option;
                BookOption opt{ Book::stringToOption(option) };

                char option_string[128];
                std::cin.getline(option_string, 128);
                std::string opt_str{option_string};
                Utilities::stripWhitespaceFrontAndBack(opt_str);
                ///
                ///error handling
                ///

                library.booksFind(opt, opt_str);
                std::cout << '\n';
            }
            else if (command == "sort") {
                std::string option;
                std::cin >> option;
                BookOption opt{ Book::stringToOption(option) };
                
                std::string sort;
                std::cin >> sort;
                BookSort srt{ Library::stringToSort(sort) };
                ///
                ///error handling
                ///
                
                library.booksSort(opt, srt);
            }
            else if (command == "add") {
                if (!checkAdminAndLog(library)) { Utilities::clearCin(); continue; }

                char c_str_title[128];
                char c_str_author[128];
                char c_str_genre[128];      
                char c_str_description[128];
                signed year;
                double rating;
                unsigned long isbn;
                Tags_t tags;
                
                std::cout << '\n';
                std::cin.get();

                std::cout << "Title: ";
                std::cin.getline(c_str_title, 128);
                std::string title{c_str_title};
                Utilities::stripWhitespaceFrontAndBack(title);
                
                std::cout << "Author: ";
                std::cin.getline(c_str_author, 128);
                std::string author{c_str_author};
                Utilities::stripWhitespaceFrontAndBack(author);

                std::cout << "Genre: ";
                std::cin.getline(c_str_genre, 128);
                std::string genre{ c_str_genre };
                Utilities::stripWhitespaceFrontAndBack(genre);

                std::cout << "Description: ";
                std::cin.getline(c_str_description, 128);
                std::string description{ c_str_description };
                Utilities::stripWhitespaceFrontAndBack(description);

                std::cout << "Year: ";
                std::cin >> year;
                std::cout << "Rating: ";
                std::cin >> rating;
                std::cout << "ISBN: ";
                std::cin >> isbn;
                
                std::cout << "Tags (commas separated): ";
                char c = std::cin.get();
                while (c == ' ' || c == '\n') {
                    c = std::cin.get();
                }

                while (c != '\n' && std::cin) {
                    std::string temp_tag;
                    while (c != ',' && c != '\n' && std::cin) {
                        temp_tag.push_back(c);
                        c = std::cin.get();
                    }
                    
                    Utilities::stripWhitespaceFrontAndBack(temp_tag);
                    if (!temp_tag.empty()) {
                        char* tag = new char[temp_tag.size() + 1];
                        strcpy_s(tag, temp_tag.size() + 1, temp_tag.c_str());
                        tags.push_back(tag);
                    }
                    
                    if (c == ',') {
                        c = std::cin.get();
                    }
                }
                ///
                ///error handling
                ///
                
                Book* book = new Book{ author, title, genre, description,
                    year, tags, rating, isbn };

                for (const char* t : tags) {
                    delete[] t;
                }

                library.booksAdd(book);
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
            else if (library.getLogLevel() != Logging::QUIET) {
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
            else if (library.getLogLevel() != Logging::QUIET) {
                std::cout << "Unknown command.\n";
            }
        }
        else if(library.getLogLevel() != Logging::QUIET) {
            std::cout << "Unknown command.\n";
        }
    }
}
