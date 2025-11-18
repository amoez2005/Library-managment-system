#include "patron.h"

#include <iostream>

Patron::Patron(int i, std::string n) : User(i, std::move(n)) {}

void Patron::show() const {
    std::cout << "Patron    ID: " << id
              << " | Name: " << name << "\n";
}
