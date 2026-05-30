#include "Menu.hpp"
#include <iostream>
#include <conio.h>
#include <string>
#include "../User/Client.hpp"
#include "../User/Admin.hpp"
#include "../User/User.hpp"
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

    bool validInput(bool fail_condition, const std::string& fail_message) {
        if (fail_condition) {
            std::cout << fail_message << '\n';
            Utilities::clearCin();
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

        Utilities::clearCin();
        std::cout << "> ";
        std::string command;
        std::cin >> command;

        if (command == "open") {
            std::string filename;
            std::cin >> filename;

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

            library.saveas(filename);
        }
        else if (command == "help") {
            std::string subcom;
            while (std::cin.peek() == ' ') {
                std::cin.get();
            }
            std::getline(std::cin, subcom);

            static std::vector<std::string> help_list{ "The following commands are supported:\n",
                    "open <file>				opens <file>\n",
                    "close					closes currently opened file\n",
                    "save					saves the currently open file\n",
                    "saveas <file>				saves the currently open file in <file>\n",
                    "help					prints this information\n",
                    "exit					exists the program\n\n",
                    "login <username> <password>		logs in as <username>\n",
                    "logout					logs out current user\n\n",
                    "books all/list				prints information about all books\n",
                    "      info/view <isbn_value>		prints detailed information about a book\n",
                    "      find <option> <option_string> 	<option> can be title, author, or tag\n",
                    "      sort <option> [asc | desc] 	<option> can be title, author, year or rating\n",
                    "      add <title> <author> <genre> 	adds book, tags are comma separated\n",
                    "      <description> <year> <rating>\n",
                    "      <isbn> <tags>\n",
                    "      remove <isbn_value>	  	removes book with <isbn_value>\n\n",
                    "users add <user> <password> <admin>	adds user (admin if argument set to 1)  \n",
                    "      remove <user>			removes user <username>\n" };

            if (!subcom.empty()) {
                bool found{ false };
                for(const std::string& str: help_list) {
                    if (str.substr(str.find_first_not_of(' '), subcom.size()) == subcom) {
                        std::cout << str;
                        found = true;
                        break;
                    }
                }
                if (!found) { std::cout << "Subcommand doesn't exist.\n"; }
            }
            else {
                for (const std::string& str : help_list) {
                    std::cout << str;
                }
            }
        }
        else if (command == "exit") {
            std::cout << "Exiting the program...\n";
            return;
        }
        else if (command == "login") {
            if (!checkFileAndLog(library)) { continue; }

            if (library.loggedIn()) { std::cout << "You are already logged in.\n"; continue; }

            std::cout << "Enter your username: ";
            std::string username;
            std::cin >> username;
            if (!validInput(Utilities::containsChar(username, User::m_DELIMITER),
                std::string{ "Username can't contain " + User::m_DELIMITER })) { continue; }

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

            if(!validInput(Utilities::containsChar(password, User::m_DELIMITER),
                std::string{ "Password can't contain " + User::m_DELIMITER })) { continue; }

            library.login(username, password);
        }
        else if (command == "logout") {
            if (!checkFileAndLog(library) || !checkLoginAndLog(library)) { continue; }

            library.logout();
        }
        else if (command == "books") {
            if (!checkFileAndLog(library) || !checkLoginAndLog(library)) { continue; }

            std::cin >> command;
            if (command == "all" || command == "list") {
                library.booksAll();
            }
            else if (command == "info" || command == "view") {
                unsigned long isbn;
                std::cin >> isbn;

                if (!validInput(!isbn, "Invalid ISBN.")) { continue; }

                library.booksInfo(isbn);
                std::cout << '\n';
            }
            else if (command == "find") {
                std::string option;
                std::cin >> option;
                BookOption opt{ Book::stringToOption(option) };

                std::string option_string;
                std::getline(std::cin >> std::ws, option_string);
                Utilities::stripWhitespaceFrontAndBack(option_string);

                library.booksFind(opt, option_string);
                std::cout << '\n';
            }
            else if (command == "sort") {
                std::string option;
                std::cin >> option;
                BookOption opt{ Book::stringToOption(option) };
                
                std::string sort;
                std::cin >> sort;
                BookSort srt{ Library::stringToSort(sort) };
                
                library.booksSort(opt, srt);
            }
            else if (command == "add") {
                if (!checkAdminAndLog(library)) { continue; }

                std::string title;
                std::string author;
                std::string genre;
                std::string description;
                signed year;
                double rating;
                unsigned long isbn;
                Tags_t tags;
                
                std::cout << '\n';
                std::cin.get();

                std::cout << "Title: ";
                std::getline(std::cin >> std::ws, title);
                Utilities::stripWhitespaceFrontAndBack(title);
                
                std::cout << "Author: ";
                std::getline(std::cin >> std::ws, author);
                Utilities::stripWhitespaceFrontAndBack(author);

                std::cout << "Genre: ";
                std::getline(std::cin >> std::ws, genre);
                Utilities::stripWhitespaceFrontAndBack(genre);

                std::cout << "Description: ";
                std::getline(std::cin >> std::ws, description);
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
                        char* tag{ new char[temp_tag.size() + 1] };
                        strcpy_s(tag, temp_tag.size() + 1, temp_tag.c_str());
                        tags.push_back(tag);
                    }
                    
                    if (c == ',') {
                        c = std::cin.get();
                    }
                }

                bool delim_found{ false };
                std::vector<std::string> vec{ title, author, genre, description};
                for (const std::string& str : vec) {
                    if (!validInput(Utilities::containsChar(str, Book::m_DELIMITER),
                        std::string{ "No field of the book can contain " } + Book::m_DELIMITER)) 
                    {
                        delim_found = true;
                        break;
                    }
                }
                for (const char* t : tags) {
                    if (!validInput(Utilities::containsChar(t, Book::m_DELIMITER),
                        std::string{ "No field of the book can contain " } + Book::m_DELIMITER)) 
                    {
                        delim_found = true;
                        break;
                    }
                }
                if (delim_found) { continue; }

                if (!validInput(!year, "Invalid year.")
                    || !validInput(!rating, "Invalid rating.")
                    || !validInput(!isbn, "Invalid ISBN.")) { continue; }


                Book* book{ new Book{ author, title, genre, description,
                    year, tags, rating, isbn } };

                for (const char* t : tags) {
                    delete[] t;
                }

                library.booksAdd(book);
            }
            else if (command == "remove") {
                if (!checkAdminAndLog(library)) { continue; }

                unsigned long isbn;
                std::cin >> isbn;

                if (!validInput(!isbn, "Invalid ISBN.")) { continue; }

                library.booksRemove(isbn);
            }
            else if (library.getLogLevel() != Logging::QUIET) {
                std::cout << "Unknown command.\n";
            }
        }
        else if (command == "users") {
            if (!checkFileAndLog(library) || !checkAdminAndLog(library)) { continue; }

            std::cin >> command;
            if (command == "add") {
                std::string username;
                std::string password;
                bool admin;
                std::cin >> username >> password >> admin;

                if (!validInput(Utilities::containsChar(username, User::m_DELIMITER),
                    std::string{ "Username can't contain " + User::m_DELIMITER })) {
                    continue;
                }
                if (!validInput(Utilities::containsChar(password, User::m_DELIMITER),
                    std::string{ "Password can't contain " + User::m_DELIMITER })) {
                    continue;
                }

                User* user;
                if (admin) {
                    user = new Admin{ username, password };
                }
                else {
                    user = new Client{ username, password };
                }
                library.usersAdd(user);
            }
            else if (command == "remove") {
                std::string username;
                std::cin >> username;

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
