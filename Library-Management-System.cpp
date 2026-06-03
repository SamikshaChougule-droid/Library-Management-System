/*
------------------------------------------
Library Management System
Developed By : Samiksha Chougule
Language     : C++
Concepts Used:
- Object Oriented Programming
- File Handling
- Functions
- Vectors
- Menu Driven Programming
------------------------------------------
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

class Book
{
public:
    int bookID;
    string title;
    string author;
    string status;

    void input()
    {
        cout << "\nEnter Book ID: ";
        cin >> bookID;

        cin.ignore();

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        status = "Available";
    }
};

string filename = "books.txt";

// Add Book
void addBook()
{
    Book b;
    b.input();

    ofstream file(filename, ios::app);

    file << b.bookID << "|"
         << b.title << "|"
         << b.author << "|"
         << b.status << endl;

    file.close();

    cout << "\nBook Added Successfully!\n";
}

// Display Books
void displayBooks()
{
    ifstream file(filename);

    string line;

    cout << "\n===== BOOK RECORDS =====\n";

    while (getline(file, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        cout << "\nBook ID : "
             << line.substr(0, p1);

        cout << "\nTitle   : "
             << line.substr(p1 + 1, p2 - p1 - 1);

        cout << "\nAuthor  : "
             << line.substr(p2 + 1, p3 - p2 - 1);

        cout << "\nStatus  : "
             << line.substr(p3 + 1);

        cout << "\n--------------------------";
    }

    file.close();
}

// Search by Title
void searchByTitle()
{
    string searchTitle;

    cin.ignore();

    cout << "\nEnter Title: ";
    getline(cin, searchTitle);

    ifstream file(filename);

    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        string title = line.substr(p1 + 1, p2 - p1 - 1);

        if (title == searchTitle)
        {
            cout << "\nBook Found!\n";
            cout << "\nBook ID : " << line.substr(0, p1);
            cout << "\nTitle   : " << title;
            cout << "\nAuthor  : "
                 << line.substr(p2 + 1, p3 - p2 - 1);
            cout << "\nStatus  : "
                 << line.substr(p3 + 1);

            found = true;
        }
    }

    if (!found)
        cout << "\nBook Not Found!\n";

    file.close();
}

// Search by Author
void searchByAuthor()
{
    string searchAuthor;

    cin.ignore();

    cout << "\nEnter Author Name: ";
    getline(cin, searchAuthor);

    ifstream file(filename);

    string line;
    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        string author = line.substr(p2 + 1, p3 - p2 - 1);

        if (author == searchAuthor)
        {
            cout << "\nBook ID : "
                 << line.substr(0, p1);

            cout << "\nTitle   : "
                 << line.substr(p1 + 1, p2 - p1 - 1);

            cout << "\nAuthor  : "
                 << author;

            cout << "\nStatus  : "
                 << line.substr(p3 + 1);

            cout << "\n--------------------------";

            found = true;
        }
    }

    if (!found)
        cout << "\nNo Books Found!\n";

    file.close();
}

// Issue Book
void issueBook()
{
    int id;

    cout << "\nEnter Book ID to Issue: ";
    cin >> id;

    ifstream file(filename);

    vector<string> records;
    string line;

    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        int bookID = stoi(line.substr(0, p1));

        if (bookID == id)
        {
            string title =
                line.substr(p1 + 1, p2 - p1 - 1);

            string author =
                line.substr(p2 + 1, p3 - p2 - 1);

            records.push_back(
                to_string(bookID) + "|" +
                title + "|" +
                author + "|Issued");

            found = true;
        }
        else
        {
            records.push_back(line);
        }
    }

    file.close();

    ofstream out(filename);

    for (string record : records)
    {
        out << record << endl;
    }

    out.close();

    if (found)
        cout << "\nBook Issued Successfully!\n";
    else
        cout << "\nBook Not Found!\n";
}

// Return Book
void returnBook()
{
    int id;

    cout << "\nEnter Book ID to Return: ";
    cin >> id;

    ifstream file(filename);

    vector<string> records;
    string line;

    bool found = false;

    while (getline(file, line))
    {
        size_t p1 = line.find('|');
        size_t p2 = line.find('|', p1 + 1);
        size_t p3 = line.find('|', p2 + 1);

        int bookID = stoi(line.substr(0, p1));

        if (bookID == id)
        {
            string title =
                line.substr(p1 + 1, p2 - p1 - 1);

            string author =
                line.substr(p2 + 1, p3 - p2 - 1);

            records.push_back(
                to_string(bookID) + "|" +
                title + "|" +
                author + "|Available");

            found = true;
        }
        else
        {
            records.push_back(line);
        }
    }

    file.close();

    ofstream out(filename);

    for (string record : records)
    {
        out << record << endl;
    }

    out.close();

    if (found)
        cout << "\nBook Returned Successfully!\n";
    else
        cout << "\nBook Not Found!\n";
}

int main()
{
    int choice;

    do
    {
        cout << "\n\n===== LIBRARY MANAGEMENT SYSTEM =====";
        cout << "\n1. Add Book";
        cout << "\n2. Display Books";
        cout << "\n3. Search by Title";
        cout << "\n4. Search by Author";
        cout << "\n5. Issue Book";
        cout << "\n6. Return Book";
        cout << "\n7. Exit";

        cout << "\nEnter Choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            addBook();
            break;

        case 2:
            displayBooks();
            break;

        case 3:
            searchByTitle();
            break;

        case 4:
            searchByAuthor();
            break;

        case 5:
            issueBook();
            break;

        case 6:
            returnBook();
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
