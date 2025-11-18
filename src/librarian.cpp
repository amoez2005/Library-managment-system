#include "librarian.h"

#include <iostream>

Librarian::Librarian(int i, std::string n) : User(i, std::move(n)) {}

void Librarian::show() const {
    std::cout << "Librarian ID: " << id
              << " | Name: " << name << "\n";
}
