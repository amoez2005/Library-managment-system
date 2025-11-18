#include "library_item.h"

LibraryItem::LibraryItem(std::string t, int i)
    : title(std::move(t)), id(i), checkedOut(false) {}

LibraryItem::~LibraryItem() = default;

int LibraryItem::getId() const { return id; }
std::string LibraryItem::getTitle() const { return title; }
bool LibraryItem::isCheckedOut() const { return checkedOut; }

void LibraryItem::checkOut() { checkedOut = true; }
void LibraryItem::returnItem() { checkedOut = false; }
