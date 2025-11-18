#include "user.h"

User::User(int i, std::string n) : id(i), name(std::move(n)) {}
User::~User() = default;

int User::getId() const { return id; }
std::string User::getName() const { return name; }
