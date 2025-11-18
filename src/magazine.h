#pragma once

#include "library_item.h"

class Magazine : public LibraryItem {
    int issue;

public:
    Magazine(std::string t, int i, int iss);
    void show() const override;
};
