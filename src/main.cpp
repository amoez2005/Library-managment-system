#include <iostream>
#include <limits>
#include <memory>
#include <string>

#include "library.h"

int main() {
    Library lib;
    int choice;

    do {
        std::cout << "\n========== Library Menu ==========\n";
        std::cout << "1. Add Book\n";
        std::cout << "2. Add Magazine\n";
        std::cout << "3. Add Patron\n";
        std::cout << "4. Add Librarian\n";
        std::cout << "5. List All Items\n";
        std::cout << "6. List All Users\n";
        std::cout << "7. Checkout Item\n";
        std::cout << "8. Return Item\n";
        std::cout << "0. Exit\n";
        std::cout << "Choice: ";
        std::cin >> choice;

        if (!std::cin) break; // simple safety

        if (choice == 1) {
            int id;
            std::string title, author;
            std::cout << "Book ID: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Title: ";
            std::getline(std::cin, title);
            std::cout << "Author: ";
            std::getline(std::cin, author);
            lib.addItem(std::make_unique<Book>(title, id, author));

        } else if (choice == 2) {
            int id, issue;
            std::string title;
            std::cout << "Magazine ID: ";
            std::cin >> id;
            std::cout << "Issue number: ";
            std::cin >> issue;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Title: ";
            std::getline(std::cin, title);
            lib.addItem(std::make_unique<Magazine>(title, id, issue));

        } else if (choice == 3) {
            int id;
            std::string name;
            std::cout << "Patron ID: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Name: ";
            std::getline(std::cin, name);
            lib.addUser(std::make_unique<Patron>(id, name));

        } else if (choice == 4) {
            int id;
            std::string name;
            std::cout << "Librarian ID: ";
            std::cin >> id;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Name: ";
            std::getline(std::cin, name);
            lib.addUser(std::make_unique<Librarian>(id, name));

        } else if (choice == 5) {
            lib.listItems();

        } else if (choice == 6) {
            lib.listUsers();

        } else if (choice == 7) {
            int itemId, userId;
            std::cout << "Item ID: ";
            std::cin >> itemId;
            std::cout << "User ID: ";
            std::cin >> userId;
            lib.checkout(itemId, userId);

        } else if (choice == 8) {
            int itemId;
            std::cout << "Item ID: ";
            std::cin >> itemId;
            lib.returnItem(itemId);
        }

    } while (choice != 0);

    std::cout << "Goodbye!\n";
    return 0;
}
