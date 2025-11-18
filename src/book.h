#pragma once

#include <string>
#include "library_item.h"

class Book : public LibraryItem {
    std::string author;

public:
    Book(std::string t, int i, std::string a);
    void show() const override;
};
