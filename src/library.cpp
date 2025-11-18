#include "library.h"

#include <iostream>

Library::~Library() {
    for (auto p : items) delete p;
    for (auto u : users) delete u;
}

void Library::addItem(LibraryItem* item) {
    items.push_back(item);
    std::cout << "Item added.\n";
}

void Library::addUser(User* u) {
    users.push_back(u);
    std::cout << "User added.\n";
}

LibraryItem* Library::findItem(int itemId) {
    for (auto p : items)
        if (p->getId() == itemId)
            return p;
    return nullptr;
}

User* Library::findUser(int userId) {
    for (auto u : users)
        if (u->getId() == userId)
            return u;
    return nullptr;
}

void Library::listItems() const {
    if (items.empty()) {
        std::cout << "No items in library.\n";
        return;
    }
    std::cout << "\n--- Library Items ---\n";
    for (auto p : items)
        p->show();
}

void Library::listUsers() const {
    if (users.empty()) {
        std::cout << "No users registered.\n";
        return;
    }
    std::cout << "\n--- Users ---\n";
    for (auto u : users)
        u->show();
}

void Library::checkout(int itemId, int userId) {
    LibraryItem* item = findItem(itemId);
    User* user = findUser(userId);

    if (!item) {
        std::cout << "Item not found.\n";
        return;
    }
    if (!user) {
        std::cout << "User not found.\n";
        return;
    }
    if (item->isCheckedOut()) {
        std::cout << "Item already checked out.\n";
        return;
    }

    item->checkOut();
    std::cout << user->getName() << " checked out \"" << item->getTitle() << "\"\n";
}

void Library::returnItem(int itemId) {
    LibraryItem* item = findItem(itemId);

    if (!item) {
        std::cout << "Item not found.\n";
        return;
    }
    if (!item->isCheckedOut()) {
        std::cout << "Item is not checked out.\n";
        return;
    }

    item->returnItem();
    std::cout << "Item returned.\n";
}
