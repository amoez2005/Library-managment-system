#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ===============================
// Base class: LibraryItem
// ===============================
class LibraryItem {
protected:
    string title;
    int id;
    bool checkedOut;
public:
    LibraryItem(string t, int i)
        : title(t), id(i), checkedOut(false) {}

    virtual ~LibraryItem() {}

    int getId() const { return id; }
    string getTitle() const { return title; }
    bool isCheckedOut() const { return checkedOut; }

    void checkOut()  { checkedOut = true; }
    void returnItem(){ checkedOut = false; }

    // Every item must show itself
    virtual void show() const = 0;
};

// ===============================
// Book (derived from LibraryItem)
// ===============================
class Book : public LibraryItem {
    string author;
public:
    Book(string t, int i, string a)
        : LibraryItem(t, i), author(a) {}

    void show() const override {
        cout << "Book   ID: " << id
             << " | Title: " << title
             << " | Author: " << author
             << " | Status: " << (checkedOut ? "Checked out" : "Available")
             << "\n";
    }
};

// ===============================
// Magazine (derived from LibraryItem)
// ===============================
class Magazine : public LibraryItem {
    int issue;
public:
    Magazine(string t, int i, int iss)
        : LibraryItem(t, i), issue(iss) {}

    void show() const override {
        cout << "Magaz. ID: " << id
             << " | Title: " << title
             << " | Issue: " << issue
             << " | Status: " << (checkedOut ? "Checked out" : "Available")
             << "\n";
    }
};

// ===============================
// Base class: User
// ===============================
class User {
protected:
    int id;
    string name;
public:
    User(int i, string n) : id(i), name(n) {}
    virtual ~User() {}

    int getId() const { return id; }
    string getName() const { return name; }

    virtual void show() const = 0;
};

// ===============================
// Patron (normal user)
// ===============================
class Patron : public User {
public:
    Patron(int i, string n) : User(i, n) {}

    void show() const override {
        cout << "Patron    ID: " << id
             << " | Name: " << name << "\n";
    }
};

// ===============================
// Librarian (admin user)
// ===============================
class Librarian : public User {
public:
    Librarian(int i, string n) : User(i, n) {}

    void show() const override {
        cout << "Librarian ID: " << id
             << " | Name: " << name << "\n";
    }
};

// ===============================
// Library class (manager)
// ===============================
class Library {
    vector<LibraryItem*> items;
    vector<User*> users;
public:
    // Destructor: clean memory
    ~Library() {
        for (auto p : items) delete p;
        for (auto u : users) delete u;
    }

    void addItem(LibraryItem* item) {
        items.push_back(item);
        cout << "Item added.\n";
    }

    void addUser(User* u) {
        users.push_back(u);
        cout << "User added.\n";
    }

    LibraryItem* findItem(int itemId) {
        for (auto p : items)
            if (p->getId() == itemId)
                return p;
        return nullptr;
    }

    User* findUser(int userId) {
        for (auto u : users)
            if (u->getId() == userId)
                return u;
        return nullptr;
    }

    void listItems() const {
        if (items.empty()) {
            cout << "No items in library.\n";
            return;
        }
        cout << "\n--- Library Items ---\n";
        for (auto p : items)
            p->show();
    }

    void listUsers() const {
        if (users.empty()) {
            cout << "No users registered.\n";
            return;
        }
        cout << "\n--- Users ---\n";
        for (auto u : users)
            u->show();
    }

    void checkout(int itemId, int userId) {
        LibraryItem* item = findItem(itemId);
        User* user = findUser(userId);

        if (!item) {
            cout << "Item not found.\n";
            return;
        }
        if (!user) {
            cout << "User not found.\n";
            return;
        }
        if (item->isCheckedOut()) {
            cout << "Item already checked out.\n";
            return;
        }

        item->checkOut();
        cout << user->getName() << " checked out \"" << item->getTitle() << "\"\n";
    }

    void returnItem(int itemId) {
        LibraryItem* item = findItem(itemId);

        if (!item) {
            cout << "Item not found.\n";
            return;
        }
        if (!item->isCheckedOut()) {
            cout << "Item is not checked out.\n";
            return;
        }

        item->returnItem();
        cout << "Item returned.\n";
    }
};

// ===============================
// main
// ===============================
int main() {
    Library lib;
    int choice;

    do {
        cout << "\n========== Library Menu ==========\n";
        cout << "1. Add Book\n";
        cout << "2. Add Magazine\n";
        cout << "3. Add Patron\n";
        cout << "4. Add Librarian\n";
        cout << "5. List All Items\n";
        cout << "6. List All Users\n";
        cout << "7. Checkout Item\n";
        cout << "8. Return Item\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        if (!cin) break; // simple safety

        if (choice == 1) {
            int id;
            string title, author;
            cout << "Book ID: ";
            cin >> id;
            cin.ignore();
            cout << "Title: ";
            getline(cin, title);
            cout << "Author: ";
            getline(cin, author);
            lib.addItem(new Book(title, id, author));

        } else if (choice == 2) {
            int id, issue;
            string title;
            cout << "Magazine ID: ";
            cin >> id;
            cout << "Issue number: ";
            cin >> issue;
            cin.ignore();
            cout << "Title: ";
            getline(cin, title);
            lib.addItem(new Magazine(title, id, issue));

        } else if (choice == 3) {
            int id;
            string name;
            cout << "Patron ID: ";
            cin >> id;
            cin.ignore();
            cout << "Name: ";
            getline(cin, name);
            lib.addUser(new Patron(id, name));

        } else if (choice == 4) {
            int id;
            string name;
            cout << "Librarian ID: ";
            cin >> id;
            cin.ignore();
            cout << "Name: ";
            getline(cin, name);
            lib.addUser(new Librarian(id, name));

        } else if (choice == 5) {
            lib.listItems();

        } else if (choice == 6) {
            lib.listUsers();

        } else if (choice == 7) {
            int itemId, userId;
            cout << "Item ID: ";
            cin >> itemId;
            cout << "User ID: ";
            cin >> userId;
            lib.checkout(itemId, userId);

        } else if (choice == 8) {
            int itemId;
            cout << "Item ID: ";
            cin >> itemId;
            lib.returnItem(itemId);
        }

    } while (choice != 0);

    cout << "Goodbye!\n";
    return 0;
}
