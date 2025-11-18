#include "book.h"

#include <iostream>

Book::Book(std::string t, int i, std::string a)
    : LibraryItem(std::move(t), i), author(std::move(a)) {}

void Book::show() const {
    std::cout << "Book   ID: " << id
              << " | Title: " << title
              << " | Author: " << author
              << " | Status: " << (checkedOut ? "Checked out" : "Available")
              << "\n";
}
