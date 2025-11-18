#pragma once

#include <vector>

#include "book.h"
#include "librarian.h"
#include "magazine.h"
#include "patron.h"

class Library {
    std::vector<LibraryItem*> items;
    std::vector<User*> users;

public:
    ~Library();

    void addItem(LibraryItem* item);
    void addUser(User* u);

    LibraryItem* findItem(int itemId);
    User* findUser(int userId);

    void listItems() const;
    void listUsers() const;

    void checkout(int itemId, int userId);
    void returnItem(int itemId);
};
