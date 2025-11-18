#pragma once

#include "user.h"

class Patron : public User {
public:
    Patron(int i, std::string n);
    void show() const override;
};
