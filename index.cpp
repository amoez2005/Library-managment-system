// -----------------------------------------------------------
// PROJECT: Library Management System
// LANGUAGE: C++ (Compiling OOP Language)
// DEMONSTRATES: Encapsulation, Inheritance, Polymorphism, Abstraction, and SOLID Principles.
// -----------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <limits> // Added for robust input handling (numeric_limits)

using namespace std; // Added using namespace std;

// ==========================================================
// 1. ABSTRACTION & INHERITANCE (Base Classes/Interfaces)
// ==========================================================

// Abstract Base Class for all Library Items
// This class demonstrates ABSTRACTION by defining a common interface
// for all items without specifying the concrete details of each item type.
class LibraryItem {
protected:
    // ENCAPSULATION: Data members are protected, accessible only to derived classes and via public methods.
    string title;
    int itemId;
    bool isCheckedOut = false;
    string itemType;

public:
    // Constructor
    LibraryItem(const string& t, int id, const string& type)
        : title(t), itemId(id), itemType(type) {}

    // Virtual destructor is crucial for proper cleanup of derived objects through a base class pointer (Polymorphism).
    virtual ~LibraryItem() = default;

    // ENCAPSULATION: Public accessor (getter) methods.
    const string& getTitle()
    const { return title; }
    int getId()
    const { return itemId; }
    const string& getType()
    const { return itemType; }
    bool getStatus()
    const { return isCheckedOut; }

    // Polymorphic methods (pure virtual functions make this an Abstract Base Class)
    // These methods demonstrate POLYMORPHISM: derived classes MUST provide their own implementation.
    virtual void displayDetails()
    const = 0;
    virtual int getLoanPeriodDays()
    const = 0; // OCP/Polymorphism: Different item types have different loan periods.

    // ENCAPSULATION: Mutator methods
    void checkOut()
    { isCheckedOut = true; }
    void returnItem()
    { isCheckedOut = false; }
};

// Abstract Base Class for all Users (demonstrates Abstraction and Inheritance)
class User {
private:
    // ENCAPSULATION: Private data members
    int userId;
    string name;

protected:
    string userType;

public:
    // Constructor
    User(int id, const string& n, const string& type)
        : userId(id), name(n), userType(type) {}

    virtual ~User() = default;

    // Getters for Encapsulation
    int getId() const { return userId; }
    const string& getName()
    const { return name; }
    const string& getType()
    const { return userType; }

    // Polymorphic method for displaying user-specific information
    virtual void displayInfo() const = 0;
};

// ==========================================================
// 2. INHERITANCE (Derived Classes)
// ==========================================================

// Concrete class inheriting from LibraryItem
// Demonstrates INHERITANCE and implements Polymorphism.
class Book : public LibraryItem {
private:
    string author;
    string isbn;

public:
    // Constructor calls base class constructor
    Book(const string& t, int id, const string& a, const string& i)
        : LibraryItem(t, id, "Book"), author(a), isbn(i) {}

    // POLYMORPHISM: Override base class function
    void displayDetails() const override {
        cout << itemType << " ID " << itemId << ": " << title << " by " << author
                  << " (ISBN: " << isbn << "). Status: "
                  << (isCheckedOut ? "Checked Out" : "Available") << ".\n";
    }

    // POLYMORPHISM: Define specific loan period (Liskov Substitution Principle)
    int getLoanPeriodDays() const override {
        return 21; // Books loan for 3 weeks
    }
};

// Another concrete class demonstrating INHERITANCE and Polymorphism
class Magazine : public LibraryItem {
private:
    int issueNumber;

public:
    // Constructor calls base class constructor
    Magazine(const string& t, int id, int issue)
        : LibraryItem(t, id, "Magazine"), issueNumber(issue) {}

    // POLYMORPHISM: Override base class function
    void displayDetails() const override {
        cout << itemType << " ID " << itemId << ": " << title
                  << " (Issue #" << issueNumber << "). Status: "
                  << (isCheckedOut ? "Checked Out" : "Available") << ".\n";
    }

    // POLYMORPHISM: Define specific loan period (Liskov Substitution Principle)
    int getLoanPeriodDays() const override {
        return 7; // Magazines loan for 1 week
    }
};

// Concrete User subclass (Patron)
class Patron : public User {
private:
    int maxItemsAllowed = 5;

public:
    // Constructor calls base class constructor
    Patron(int id, const string& n) : User(id, n, "Patron") {}

    // POLYMORPHISM: Override base class function
    void displayInfo() const override {
        cout << "User ID " << getId() << " (" << userType << "): " << getName()
                  << ". Max items: " << maxItemsAllowed << ".\n";
    }
    // Liskov Substitution Principle (LSP) suggested by a Patron being used
    // wherever a general User is expected, but with specific capabilities.
};

// Concrete User subclass (Librarian)
class Librarian : public User {
public:
    // Constructor calls base class constructor
    Librarian(int id, const string& n) : User(id, n, "Librarian") {}

    // POLYMORPHISM: Override base class function
    void displayInfo() const override {
        cout << "User ID " << getId() << " (" << userType << "): " << getName()
                  << ". (Full management privileges).\n";
    }

    // Specific method for Librarian (Interface Segregation Principle suggested)
    void manageUsers() const {
        cout << getName() << " is managing user accounts and fines.\n";
    }
};

// ==========================================================
// 3. SERVICE & MANAGER (SOLID Principles)
// ==========================================================

// ILibraryService: Defines the high-level contract (Abstraction & Dependency Inversion)
// This abstract class serves as an INTERFACE (I in SOLID) and ensures DIP (D in SOLID)
// by making high-level components (like the main function) depend on this abstraction.
class ILibraryService {
public:
    virtual ~ILibraryService() = default;
    virtual void addItem(unique_ptr<LibraryItem> item) = 0; // S in SOLID (managing items)
    virtual void registerUser(unique_ptr<User> user) = 0; // S in SOLID (managing users)
    virtual bool checkoutItem(int itemId, int userId) = 0; // Transactional
    virtual bool returnItem(int itemId) = 0; // Transactional
    virtual void listAllItems() const = 0;
};


// LibraryManager: Concrete implementation of the service
// Demonstrates Single Responsibility (S), Open/Closed (O), and Dependency Inversion (D)
class LibraryManager : public ILibraryService {
private:
    // Using smart pointers for safe memory management and ownership
    vector<unique_ptr<LibraryItem>> items;
    vector<unique_ptr<User>> users;

private: // Reverted to private for stronger encapsulation
    // Helper method to find an item (adheres to SRP)
    LibraryItem* findItem(int itemId) {
        auto it = find_if(items.begin(), items.end(),
            [itemId](const unique_ptr<LibraryItem>& item) {
                return item->getId() == itemId;
            });
        return (it != items.end()) ? it->get() : nullptr;
    }

public: // findUser remains public for the main demo loop
    // Helper method to find a user (adheres to SRP) - MADE PUBLIC FOR MAIN DEMO
    User* findUser(int userId) {
        auto it = find_if(users.begin(), users.end(),
            [userId](const unique_ptr<User>& user) {
                return user->getId() == userId;
            });
        return (it != users.end()) ? it->get() : nullptr;
    }

public:
    // Single Responsibility Principle (SRP): This class is responsible for library business logic.

    // OCP: Allows adding new item types without modifying this core transaction logic,
    // as long as the new item inherits from LibraryItem (e.g., adding a 'DVD' class works).
    void addItem(unique_ptr<LibraryItem> item) override {
        cout << "[MANAGER] Adding " << item->getType() << ": " << item->getTitle() << ".\n";
        items.push_back(move(item));
    }

    void registerUser(unique_ptr<User> user) override {
        cout << "[MANAGER] Registering " << user->getType() << ": " << user->getName() << ".\n";
        users.push_back(move(user));
    }

    bool checkoutItem(int itemId, int userId) override {
        LibraryItem* item = findItem(itemId);
        User* user = findUser(userId);

        if (!item) {
            cerr << "[ERROR] Checkout failed: Item ID " << itemId << " not found.\n";
            return false;
        }
        if (!user) {
            cerr << "[ERROR] Checkout failed: User ID " << userId << " not found.\n";
            return false;
        }
        if (item->getStatus()) {
            cerr << "[INFO] Item " << item->getTitle() << " is already checked out.\n";
            return false;
        }

        // Liskov Substitution Principle (LSP): We call getType() on the item, which correctly
        // delegates to the actual derived type (Book, Magazine, etc.).
        cout << "\n[TRANSACTION] Checking out " << item->getType() << " '" << item->getTitle()
                  << "' for " << user->getName() << ".\n";

        item->checkOut();
        // Demonstrate Polymorphism/LSP: Accessing the loan period specific to the item type.
        cout << "--> Loan period for this item is " << item->getLoanPeriodDays() << " days.\n";

        return true;
    }

    bool returnItem(int itemId) override {
        LibraryItem* item = findItem(itemId);

        if (!item) {
            cerr << "[ERROR] Return failed: Item ID " << itemId << " not found.\n";
            return false;
        }
        if (!item->getStatus()) {
            cerr << "[INFO] Item " << item->getTitle() << " is already available.\n";
            return false;
        }

        cout << "[TRANSACTION] Returning " << item->getType() << " '" << item->getTitle() << "'.\n";
        item->returnItem();
        return true;
    }

    void listAllItems() const override {
        cout << "\n--- Current Library Inventory ---\n";
        if (items.empty()) {
            cout << "The library is empty.\n";
            return;
        }
        // POLYMORPHISM: Iterating through the base class pointer (LibraryItem*) and calling
        // the virtual function displayDetails(), which executes the correct derived function.
        for (const auto& item : items) {
            item->displayDetails();
        }
        cout << "---------------------------------\n";
    }

    void listAllUsers() const {
        cout << "\n--- Registered Users ---\n";
        if (users.empty()) {
            cout << "No users registered.\n";
            return;
        }
        // POLYMORPHISM: Iterating through the base class pointer (User*) and calling
        // the virtual function displayInfo().
        for (const auto& user : users) {
            user->displayInfo();
        }
        cout << "----------------------\n";
    }
};

// ==========================================================
// 4. MAIN INTERACTIVE DEMONSTRATION
// ==========================================================

// Helper function to get integer input safely
int getIntInput(const string& prompt) {
    int value;
    cout << prompt;
    // Loop until valid integer is entered
    while (!(cin >> value)) {
        cout << "Invalid input. Please enter a number: ";
        cin.clear(); // Clear the error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard bad input
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear rest of line
    return value;
}

// Helper function to get string input safely
string getStringInput(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

void displayMenu() {
    cout << "\n========================================\n";
    cout << "  Library Management System Menu\n";
    cout << "========================================\n";
    cout << "1. Add New Item (Book/Magazine)\n";
    cout << "2. Register New User (Patron/Librarian)\n";
    cout << "3. Checkout Item\n";
    cout << "4. Return Item\n";
    cout << "5. List All Items\n";
    cout << "6. List All Users\n";
    cout << "7. Librarian Action (Manage Users)\n";
    cout << "0. Exit\n";
    cout << "----------------------------------------\n";
}

void handleAddItem(ILibraryService* library) {
    cout << "\n--- Add Item ---\n";
    string type = getStringInput("Enter item type (book/magazine): ");
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    if (type == "book") {
        string title = getStringInput("Enter Book Title: ");
        int id = getIntInput("Enter Book ID (e.g., 101): ");
        string author = getStringInput("Enter Author Name: ");
        string isbn = getStringInput("Enter ISBN: ");
        library->addItem(make_unique<Book>(title, id, author, isbn));
    } else if (type == "magazine") {
        string title = getStringInput("Enter Magazine Title: ");
        int id = getIntInput("Enter Magazine ID (e.g., 201): ");
        int issue = getIntInput("Enter Issue Number: ");
        library->addItem(make_unique<Magazine>(title, id, issue));
    } else {
        cout << "[ERROR] Invalid item type. Please enter 'book' or 'magazine'.\n";
    }
}

void handleRegisterUser(ILibraryService* library) {
    cout << "\n--- Register User ---\n";
    string type = getStringInput("Enter user type (patron/librarian): ");
    transform(type.begin(), type.end(), type.begin(), ::tolower);

    string name = getStringInput("Enter User Name: ");
    int id = getIntInput("Enter User ID (e.g., 1): ");


    if (type == "patron") {
        library->registerUser(make_unique<Patron>(id, name));
    } else if (type == "librarian") {
        library->registerUser(make_unique<Librarian>(id, name));
    } else {
        cout << "[ERROR] Invalid user type. Please enter 'patron' or 'librarian'.\n";
    }
}

void handleCheckout(ILibraryService* library) {
    cout << "\n--- Checkout Item ---\n";
    int itemId = getIntInput("Enter Item ID to checkout: ");
    int userId = getIntInput("Enter User ID checking out: ");
    library->checkoutItem(itemId, userId);
}

void handleReturn(ILibraryService* library) {
    cout << "\n--- Return Item ---\n";
    int itemId = getIntInput("Enter Item ID to return: ");
    library->returnItem(itemId);
}

void handleLibrarianAction(LibraryManager* manager) {
    cout << "\n--- Librarian Action ---\n";
    int userId = getIntInput("Enter Librarian User ID: ");

    User* userPtr = manager->findUser(userId);

    if (Librarian* bob = dynamic_cast<Librarian*>(userPtr)) {
        bob->manageUsers();
    } else if (userPtr) {
        cout << "[ERROR] User ID " << userId << " is " << userPtr->getType() << ", not a Librarian. Access denied.\n";
    } else {
        cout << "[ERROR] User ID " << userId << " not found.\n";
    }
}


int main() {
    // -----------------------------------------------------------
    // SOLID: Dependency Inversion Principle (DIP)
    // The high-level module depends on the ABSTRACTION (ILibraryService).
    // -----------------------------------------------------------
    cout << "--- Initializing Library System ---\n";

    // Initialize the concrete manager class via the abstract interface.
    unique_ptr<ILibraryService> library = make_unique<LibraryManager>();

    // Get the concrete pointer for actions not defined in the interface (like listAllUsers and findUser for the demo).
    LibraryManager* manager = dynamic_cast<LibraryManager*>(library.get());

    int choice;
    do {
        displayMenu();
        choice = getIntInput("Enter your choice (0-7): ");

        switch (choice) {
            case 1:
                handleAddItem(library.get());
                break;
            case 2:
                handleRegisterUser(library.get());
                break;
            case 3:
                handleCheckout(library.get());
                break;
            case 4:
                handleReturn(library.get());
                break;
            case 5:
                library->listAllItems();
                break;
            case 6:
                manager->listAllUsers();
                break;
            case 7:
                handleLibrarianAction(manager);
                break;
            case 0:
                cout << "\n--- System Shutdown ---\n";
                cout << "Thank you for using the Library Management System. Goodbye!\n";
                break;
            default:
                cout << "[ERROR] Invalid choice. Please try again.\n";
                break;
        }

    } while (choice != 0);

    return 0;
}
