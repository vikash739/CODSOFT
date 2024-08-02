#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <ctime>

using namespace std;

struct Book {
    string title;
    string author;
    string ISBN;
    bool available;

    Book(string t, string a, string i) : title(t), author(a), ISBN(i), available(true) {}
};

struct Borrower {
    string name;
    string borrowedISBN;
    time_t borrowDate;

    Borrower(string n, string isbn, time_t bd) : name(n), borrowedISBN(isbn), borrowDate(bd) {}
};

void displayMenu() {
    cout << "\nLibrary Management System" << endl;
    cout << "-------------------------" << endl;
    cout << "1. Search for a Book" << endl;
    cout << "2. Check Out a Book" << endl;
    cout << "3. Return a Book" << endl;
    cout << "4. View Borrowers" << endl;
    cout << "5. Exit" << endl;
    cout << "-------------------------" << endl;
}

void searchBook(const vector<Book>& books) {
    int choice;
    cout << "\nSearch Book by:" << endl;
    cout << "1. Title" << endl;
    cout << "2. Author" << endl;
    cout << "3. ISBN" << endl;
    cout << "Enter your choice (1-3): ";
    cin >> choice;
    cin.ignore();

    string query;
    cout << "Enter your search query: ";
    getline(cin, query);

    bool found = false;
    for (const auto& book : books) {
        if ((choice == 1 && book.title == query) ||
            (choice == 2 && book.author == query) ||
            (choice == 3 && book.ISBN == query)) {
            cout << "Book Found: " << book.title << " by " << book.author << " (ISBN: " << book.ISBN << ") - "
                 << (book.available ? "Available" : "Checked Out") << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No book found with the given query." << endl;
    }
}

void checkOutBook(vector<Book>& books, vector<Borrower>& borrowers) {
    string borrowerName;
    string isbn;

    cout << "Enter Borrower Name: ";
    cin.ignore();
    getline(cin, borrowerName);
    cout << "Enter Book ISBN: ";
    getline(cin, isbn);

    for (auto& book : books) {
        if (book.ISBN == isbn) {
            if (book.available) {
                book.available = false;
                time_t now = time(0);
                borrowers.emplace_back(borrowerName, isbn, now);
                cout << "Book '" << book.title << "' checked out to " << borrowerName << "." << endl;
            } else {
                cout << "Book '" << book.title << "' is currently checked out." << endl;
            }
            return;
        }
    }
    cout << "No book found with ISBN " << isbn << "." << endl;
}

void returnBook(vector<Book>& books, vector<Borrower>& borrowers) {
    string isbn;
    cout << "Enter Book ISBN to return: ";
    cin.ignore();
    getline(cin, isbn);

    for (auto& book : books) {
        if (book.ISBN == isbn) {
            if (!book.available) {
                book.available = true;
                for (auto it = borrowers.begin(); it != borrowers.end(); ++it) {
                    if (it->borrowedISBN == isbn) {
                        time_t now = time(0);
                        double seconds = difftime(now, it->borrowDate);
                        int days = seconds / (60 * 60 * 24);
                        double fine = max(0, days - 14) * 0.50;
                        cout << "Book '" << book.title << "' returned by " << it->name << "." << endl;
                        cout << "Overdue by " << max(0, days - 14) << " days. Fine: $" << fine << endl;
                        borrowers.erase(it);
                        return;
                    }
                }
            } else {
                cout << "Book '" << book.title << "' was not checked out." << endl;
            }
            return;
        }
    }
    cout << "No book found with ISBN " << isbn << "." << endl;
}

void viewBorrowers(const vector<Borrower>& borrowers) {
    if (borrowers.empty()) {
        cout << "\nNo borrowers." << endl;
    } else {
        cout << "\nCurrent Borrowers:" << endl;
        for (const auto& borrower : borrowers) {
            cout << borrower.name << " has borrowed ISBN " << borrower.borrowedISBN << endl;
        }
    }
}

int main() {
    vector<Book> books = {
        {"The Little Prince", "Antoine de Saint-Exupéry", "1234567890"},
        {"Charlotte's Web", "E.B. White", "1234567891"},
        {"Where the Wild Things Are", "Maurice Sendak", "1234567892"},
        {"The Very Hungry Caterpillar", "Eric Carle", "1234567893"},
        {"Goodnight Moon", "Margaret Wise Brown", "1234567894"},
        {"Green Eggs and Ham", "Dr. Seuss", "1234567895"},
        {"Matilda", "Roald Dahl", "1234567896"},
        {"Harry Potter and the Sorcerer's Stone", "J.K. Rowling", "1234567897"},
        {"The Tale of Peter Rabbit", "Beatrix Potter", "1234567898"},
        {"Alice's Adventures in Wonderland", "Lewis Carroll", "1234567899"}
    };

    vector<Borrower> borrowers;
    
    while (true) {
        displayMenu();
        int choice;
        cout << "Enter your choice (1-5): ";
        cin >> choice;

        switch (choice) {
            case 1:
                searchBook(books);
                break;
            case 2:
                checkOutBook(books, borrowers);
                break;
            case 3:
                returnBook(books, borrowers);
                break;
            case 4:
                viewBorrowers(borrowers);
                break;
            case 5:
                cout << "Exiting the Library Management System. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please enter a number between 1 and 5." << endl;
        }
    }
}
