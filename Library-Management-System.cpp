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

// ================= BOOK CLASS =================
class Book {
public:
    int bookID;
    string title;
    string author;
    bool issued;
    int issuedToMemberID;

    Book() {}

    Book(int id, string t, string a, bool isIssued = false, int memberID = -1) {
        bookID = id;
        title = t;
        author = a;
        issued = isIssued;
        issuedToMemberID = memberID;
    }
};

// ================= MEMBER CLASS =================
class Member {
public:
    int memberID;
    string memberName;

    Member() {}

    Member(int id, string name) {
        memberID = id;
        memberName = name;
    }
};

// ================= LIBRARY CLASS =================
class Library {
private:
    vector<Book> books;
    vector<Member> members;

public:

    // -------- LOAD BOOKS --------
    void loadBooks() {
        books.clear();

        ifstream file("books.txt");

        if (!file)
            return;

        string line;

        while (getline(file, line)) {
            size_t p1 = line.find('|');
            size_t p2 = line.find('|', p1 + 1);
            size_t p3 = line.find('|', p2 + 1);
            size_t p4 = line.find('|', p3 + 1);

            if (p1 == string::npos || p2 == string::npos ||
                p3 == string::npos || p4 == string::npos)
                continue;

            int id = stoi(line.substr(0, p1));
            string title = line.substr(p1 + 1, p2 - p1 - 1);
            string author = line.substr(p2 + 1, p3 - p2 - 1);
            bool issued = stoi(line.substr(p3 + 1, p4 - p3 - 1));
            int memberID = stoi(line.substr(p4 + 1));

            books.push_back(Book(id, title, author, issued, memberID));
        }

        file.close();
    }

    // -------- SAVE BOOKS --------
    void saveBooks() {
        ofstream file("books.txt");

        for (auto &book : books) {
            file << book.bookID << "|"
                 << book.title << "|"
                 << book.author << "|"
                 << book.issued << "|"
                 << book.issuedToMemberID << endl;
        }

        file.close();
    }

    // -------- LOAD MEMBERS --------
    void loadMembers() {
        members.clear();

        ifstream file("members.txt");

        if (!file)
            return;

        string line;

        while (getline(file, line)) {
            size_t p1 = line.find('|');

            if (p1 == string::npos)
                continue;

            int id = stoi(line.substr(0, p1));
            string name = line.substr(p1 + 1);

            members.push_back(Member(id, name));
        }

        file.close();
    }

    // -------- SAVE MEMBERS --------
    void saveMembers() {
        ofstream file("members.txt");

        for (auto &member : members) {
            file << member.memberID << "|"
                 << member.memberName << endl;
        }

        file.close();
    }

    // -------- ADD BOOK --------
    void addBook() {
        int id;
        string title, author;

        cout << "\nEnter Book ID: ";
        cin >> id;
        cin.ignore();

        for (auto &book : books) {
            if (book.bookID == id) {
                cout << "\nBook ID already exists!\n";
                return;
            }
        }

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));

        saveBooks();

        cout << "\nBook Added Successfully!\n";
    }

    // -------- VIEW BOOKS --------
    void viewBooks() {
        if (books.empty()) {
            cout << "\nNo Books Available!\n";
            return;
        }

        cout << "\n=====================================================================================\n";
        cout << left
             << setw(10) << "ID"
             << setw(30) << "Title"
             << setw(25) << "Author"
             << setw(15) << "Status"
             << setw(15) << "Member ID" << endl;

        cout << "=====================================================================================\n";

        for (auto &book : books) {
            cout << left
                 << setw(10) << book.bookID
                 << setw(30) << book.title
                 << setw(25) << book.author
                 << setw(15) << (book.issued ? "Issued" : "Available")
                 << setw(15)
                 << (book.issued ? to_string(book.issuedToMemberID) : "-")
                 << endl;
        }
    }

    // -------- ADD MEMBER --------
    void addMember() {
        int id;
        string name;

        cout << "\nEnter Member ID: ";
        cin >> id;
        cin.ignore();

        for (auto &member : members) {
            if (member.memberID == id) {
                cout << "\nMember ID already exists!\n";
                return;
            }
        }

        cout << "Enter Member Name: ";
        getline(cin, name);

        members.push_back(Member(id, name));

        saveMembers();

        cout << "\nMember Added Successfully!\n";
    }

    // -------- VIEW MEMBERS --------
    void viewMembers() {
        if (members.empty()) {
            cout << "\nNo Members Available!\n";
            return;
        }

        cout << "\n=====================================\n";
        cout << left
             << setw(15) << "Member ID"
             << setw(25) << "Member Name" << endl;

        cout << "=====================================\n";

        for (auto &member : members) {
            cout << left
                 << setw(15) << member.memberID
                 << setw(25) << member.memberName << endl;
        }
    }

    // -------- SEARCH TITLE --------
    void searchByTitle() {
        string title;
        cin.ignore();

        cout << "\nEnter Title to Search: ";
        getline(cin, title);

        bool found = false;

        for (auto &book : books) {
            if (book.title.find(title) != string::npos) {
                cout << "\nBook Found!\n";
                cout << "ID: " << book.bookID << endl;
                cout << "Title: " << book.title << endl;
                cout << "Author: " << book.author << endl;
                cout << "Status: "
                     << (book.issued ? "Issued" : "Available") << endl;

                found = true;
            }
        }

        if (!found)
            cout << "\nNo Book Found!\n";
    }

    // -------- SEARCH AUTHOR --------
    void searchByAuthor() {
        string author;
        cin.ignore();

        cout << "\nEnter Author Name: ";
        getline(cin, author);

        bool found = false;

        for (auto &book : books) {
            if (book.author.find(author) != string::npos) {
                cout << "\nBook Found!\n";
                cout << "ID: " << book.bookID << endl;
                cout << "Title: " << book.title << endl;
                cout << "Author: " << book.author << endl;
                cout << "Status: "
                     << (book.issued ? "Issued" : "Available") << endl;

                found = true;
            }
        }

        if (!found)
            cout << "\nNo Book Found!\n";
    }

    // -------- ISSUE BOOK --------
    void issueBook() {
        int bookID, memberID;

        cout << "\nEnter Book ID to Issue: ";
        cin >> bookID;

        cout << "Enter Member ID: ";
        cin >> memberID;

        bool memberExists = false;

        for (auto &member : members) {
            if (member.memberID == memberID) {
                memberExists = true;
                break;
            }
        }

        if (!memberExists) {
            cout << "\nMember ID not found!\n";
            return;
        }

        for (auto &book : books) {
            if (book.bookID == bookID) {

                if (book.issued) {
                    cout << "\nBook already issued!\n";
                    return;
                }

                book.issued = true;
                book.issuedToMemberID = memberID;

                saveBooks();

                cout << "\nBook Issued Successfully!\n";
                return;
            }
        }

        cout << "\nBook Not Found!\n";
    }

    // -------- RETURN BOOK --------
    void returnBook() {
        int bookID;

        cout << "\nEnter Book ID to Return: ";
        cin >> bookID;

        for (auto &book : books) {

            if (book.bookID == bookID) {

                if (!book.issued) {
                    cout << "\nBook was not issued!\n";
                    return;
                }

                book.issued = false;
                book.issuedToMemberID = -1;

                saveBooks();

                cout << "\nBook Returned Successfully!\n";
                return;
            }
        }

        cout << "\nBook Not Found!\n";
    }
};

// ================= MAIN FUNCTION =================
int main() {

    Library library;

    library.loadBooks();
    library.loadMembers();

    int choice;

    do {
        cout << "\n\n========= LIBRARY MANAGEMENT SYSTEM =========\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Add Member\n";
        cout << "4. View Members\n";
        cout << "5. Search Book by Title\n";
        cout << "6. Search Book by Author\n";
        cout << "7. Issue Book\n";
        cout << "8. Return Book\n";
        cout << "9. Exit\n";
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
            library.addMember();
            break;

        case 4:
            library.viewMembers();
            break;

        case 5:
            library.searchByTitle();
            break;

        case 6:
            library.searchByAuthor();
            break;

        case 7:
            library.issueBook();
            break;

        case 8:
            library.returnBook();
            break;

        case 9:
            cout << "\nThank You!\n";
            break;

        default:
            cout << "\nInvalid Choice!\n";
        }

    } while (choice != 9);

    return 0;
}
