#include "library.h"

#include <iostream>

void Library::addItem(std::unique_ptr<LibraryItem> item) {
    items.push_back(std::move(item));
    std::cout << "Item added.\n";
}

void Library::addUser(std::unique_ptr<User> u) {
    users.push_back(std::move(u));
    std::cout << "User added.\n";
}

LibraryItem* Library::findItem(int itemId) {
    for (const auto& p : items)
        if (p->getId() == itemId)
            return p.get();
    return nullptr;
}

User* Library::findUser(int userId) {
    for (const auto& u : users)
        if (u->getId() == userId)
            return u.get();
    return nullptr;
}

void Library::listItems() const {
    if (items.empty()) {
        std::cout << "No items in library.\n";
        return;
    }
    std::cout << "\n--- Library Items ---\n";
    for (const auto& p : items)
        p->show();
}

void Library::listUsers() const {
    if (users.empty()) {
        std::cout << "No users registered.\n";
        return;
    }
    std::cout << "\n--- Users ---\n";
    for (const auto& u : users)
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
