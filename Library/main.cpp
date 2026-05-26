#include <iostream>
#include <string>
#include "Library.hpp"

///commands with no prototypes:
///open, close, save, saveas

//verboseness toggle

void menu(Library& library) {
    bool first_run{true};
    while(true) {
        if(!first_run) {
            std::cout << '\n';
            first_run = false;
        }
        std::string command;
        std::cout << "> ";
        std::cin >> command;

        if(command == "open") {
            ///
        }
        else if(command == "close") {
            ///
        }
        else if(command == "save") {
            ///
        }
        else if(command == "saveas") {
            ///
        }
        else if(command == "help") {
            std::cout << "The following commands are supported:\n"
                      << "open <file>				opens <file>\n"
                      << "close					closes currently opened file\n"
                      << "save					saves the currently open file\n"
                      << "saveas <file>				saves the currently open file in <file>\n"
                      << "help					prints this information\n"
                      << "exit					exists the program\n\n"
                      << "login <username> <password>		logs in\n"
                      << "logout					logs out\n\n"
                         "books all				prints information about all books\n"
                      << "      info/view <isbn_value>		prints detailed information about a book\n"
                      << "      find <option> <option_string> 	<option> can be title, author, or tag\n"
                      << "      sort <option> [asc | desc] 	<option> can be title, author, or tag\n"
                      << "      add 	 adds book\n"      ////////////////////////////////////
                      << "      remove 	 removes book\n\n" ////////////////////////////////
                      << "users add <user> <password>		adds user\n"
                      << "      remove <user>			removes user\n";
        }
        else if(command == "exit") {
            std::cout << "Exiting the program...\n";
            return;
        }
        else if(command == "login") {
            ///
        }
        else if(command == "logout") {
            ///
        }
        else if(command == "books") {
            std::cin >> command;
            if(command == "all") {
                library.booksAll();
            }
            else if(command == "info" || command == "view") {
                ///
            }
            else if(command == "find") {
                ///
            }
            else if(command == "sort") {
                ///
            }
            else if(command == "add") {
                ///
            }
            else if(command == "remove") {
                ///
            }
            else {
                std::cout << "Command doesn't exist.\n";
            }
        }
        else if(command == "users") {
            if(command == "add") {
                ///
            }
            else if(command == "remove") {
                ///
            }
            else {
                std::cout << "Command doesn't exist.\n";
            }
        }
        else {
            std::cout << "Command doesn't exist.\n";
        }
    }
}

int main() {
    Library lib;
    lib.usersAdd(new Client{ "client", "bbb" });
    lib.booksAdd(new Book{"Frank Herbert", "Dune", "Science Fiction",
                          "A mythic and emotionally charged hero's journey set on the desert planet Arrakis.",
                          1965, Tags_t{"Sci-Fi", "Classic", "Space Opera", "Politics"}, 4.54, 0441172717});

    menu(lib);
    
    // Book b{"Frank Herbert",
    //                       "Dune",
    //                       "Science Fiction",
    //                       "A mythic and emotionally charged hero's journey set on the desert planet Arrakis.",
    //                       1965,
    //                       Tags_t{"Sci-Fi", "Classic", "Space Opera", "Politics"},
    //                       4.54,
    //                       0441172717};

    // Book *copy_of_b = Book::deserialize("Library.dat", 2);
    // delete copy_of_b;
    // b.serialize("Library.dat");

    // lib.usersRemove("client");

    // lib.booksInfo(0441172717);
    // lib.booksAll();

    // for (const auto* u : users) {
    //     u->serialize("Library.dat");
    // }

    // User* copy_of_admin = User::deserialize("Library.dat", 0);
    // User* copy_of_client = User::deserialize("Library.dat", 1);
    // delete copy_of_client;
    // delete copy_of_admin;
    //return 0;
}