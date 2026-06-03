/*
------------------------------------------
Library Management System
Developed By : Samiksha Chougule
Language     : C++
Concepts Used:
- Object Oriented Programming
- File Handling
- Classes
- Vectors
- Menu Driven Programming
------------------------------------------
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

class Book {
public:
    int bookID;
    string title;
    string author;
    bool issued;

    Book() {}

    Book(int id, string t, string a, bool isIssued = false) {
        bookID = id;
        title = t;
        author = a;
        issued = isIssued;
    }
};

class Library {
private:
    vector<Book> books;

public:
    void loadBooks() {
        books.clear();

        ifstream file("books.txt");

        if (!file) {
            return;
        }

        string line;

        while (getline(file, line)) {
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);

            if (p1 == string::npos || p2 == string::npos || p3 == string::npos)
                continue;

            int id = stoi(line.substr(0, p1));
            string title = line.substr(p1 + 1, p2 - p1 - 1);
            string author = line.substr(p2 + 1, p3 - p2 - 1);
            bool issued = stoi(line.substr(p3 + 1));

            books.push_back(Book(id, title, author, issued));
        }

        file.close();
    }

    void saveBooks() {
        ofstream file("books.txt");

        for (auto &book : books) {
            file << book.bookID << "|"
                 << book.title << "|"
                 << book.author << "|"
                 << book.issued << endl;
        }

        file.close();
    }

    void addBook() {
        int id;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author, false));

        saveBooks();

        cout << "\nBook Added Successfully!\n";
    }

    void viewBooks() {
        if (books.empty()) {
            cout << "\nNo Books Available!\n";
            return;
        }

        cout << "\n====================================================================\n";
        cout << left
             << setw(10) << "ID"
             << setw(30) << "Title"
             << setw(25) << "Author"
             << setw(10) << "Status" << endl;
        cout << "====================================================================\n";

        for (auto &book : books) {
            cout << left
                 << setw(10) << book.bookID
                 << setw(30) << book.title
                 << setw(25) << book.author
                 << setw(10) << (book.issued ? "Issued" : "Available")
                 << endl;
        }
    }

    void searchByTitle() {
        string title;
        cin.ignore();

        cout << "\nEnter Title to Search: ";
        getline(cin, title);

        bool found = false;

        for (auto &book : books) {
            if (book.title.find(title) != string::npos) {
                cout << "\nBook Found\n";
                cout << "ID: " << book.bookID << endl;
                cout << "Title: " << book.title << endl;
                cout << "Author: " << book.author << endl;
                cout << "Status: "
                     << (book.issued ? "Issued" : "Available")
                     << endl;

                found = true;
            }
        }

        if (!found)
            cout << "\nNo Book Found!\n";
    }

    void searchByAuthor() {
        string author;
        cin.ignore();

        cout << "\nEnter Author Name: ";
        getline(cin, author);

        bool found = false;

        for (auto &book : books) {
            if (book.author.find(author) != string::npos) {
                cout << "\nBook Found\n";
                cout << "ID: " << book.bookID << endl;
                cout << "Title: " << book.title << endl;
                cout << "Author: " << book.author << endl;
                cout << "Status: "
                     << (book.issued ? "Issued" : "Available")
                     << endl;

                found = true;
            }
        }

        if (!found)
            cout << "\nNo Book Found!\n";
    }

    void issueBook() {
        int id;

        cout << "\nEnter Book ID to Issue: ";
        cin >> id;

        for (auto &book : books) {
            if (book.bookID == id) {

                if (book.issued) {
                    cout << "\nBook Already Issued!\n";
                    return;
                }

                book.issued = true;

                saveBooks();

                cout << "\nBook Issued Successfully!\n";
                return;
            }
        }

        cout << "\nBook Not Found!\n";
    }

    void returnBook() {
        int id;

        cout << "\nEnter Book ID to Return: ";
        cin >> id;

        for (auto &book : books) {
            if (book.bookID == id) {

                if (!book.issued) {
                    cout << "\nThis Book Was Not Issued!\n";
                    return;
                }

                book.issued = false;

                saveBooks();

                cout << "\nBook Returned Successfully!\n";
                return;
            }
        }

        cout << "\nBook Not Found!\n";
    }
};

int main() {
    Library library;
    library.loadBooks();

    int choice;

    do {
        cout << "\n\n========== LIBRARY MANAGEMENT SYSTEM ==========\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book by Title\n";
        cout << "4. Search Book by Author\n";
        cout << "5. Issue Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            library.addBook();
            break;

        case 2:
            library.viewBooks();
            break;

        case 3:
            library.searchByTitle();
            break;

        case 4:
            library.searchByAuthor();
            break;

        case 5:
            library.issueBook();
            break;

        case 6:
            library.returnBook();
            break;

        case 7:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 7);

    return 0;
}
