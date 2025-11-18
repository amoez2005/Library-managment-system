#include "magazine.h"

#include <iostream>

Magazine::Magazine(std::string t, int i, int iss)
    : LibraryItem(std::move(t), i), issue(iss) {}

void Magazine::show() const {
    std::cout << "Magaz. ID: " << id
              << " | Title: " << title
              << " | Issue: " << issue
              << " | Status: " << (checkedOut ? "Checked out" : "Available")
              << "\n";
}
