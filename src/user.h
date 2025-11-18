#pragma once

#include <string>

class User {
protected:
    int id;
    std::string name;

public:
    User(int i, std::string n);
    virtual ~User();

    int getId() const;
    std::string getName() const;

    virtual void show() const = 0;
};
