#pragma once

#include <string>

class LibraryItem {
protected:
    std::string title;
    int id;
    bool checkedOut;

public:
    LibraryItem(std::string t, int i);
    virtual ~LibraryItem();

    int getId() const;
    std::string getTitle() const;
    bool isCheckedOut() const;

    void checkOut();
    void returnItem();

    virtual void show() const = 0;
};
