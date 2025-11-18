#pragma once

#include <memory>
#include <vector>

#include "book.h"
#include "librarian.h"
#include "magazine.h"
#include "patron.h"

class Library {
    std::vector<std::unique_ptr<LibraryItem>> items;
    std::vector<std::unique_ptr<User>> users;

public:
    Library() = default;
    ~Library() = default;

    void addItem(std::unique_ptr<LibraryItem> item);
    void addUser(std::unique_ptr<User> u);

    LibraryItem* findItem(int itemId);
    User* findUser(int userId);

    void listItems() const;
    void listUsers() const;

    void checkout(int itemId, int userId);
    void returnItem(int itemId);
};
