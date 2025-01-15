#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include <limits>
#include <ios>
#include "Library.cpp"
#include "Reader.cpp"
#include "Book.cpp"

using std::cout;
using std::cin;
using std::string;
using std::getline;

bool running = true;

enum class Option
{
    EXIT = 0,
    ADD_BOOK,
    EDIT_BOOK,
    DELETE_BOOK,
    SEARCH_BOOK,
    DISPLAY_BOOKS,
    ADD_READER,
    DELETE_READER,
    MANAGE_BORROWED,
    RETURN_BOOK,
    DISPLAY_READERS,
    SAVE,
    INVALID
};

void wPause();
void clearScreen();
void addBookOption(Library &library);
void editBookOption(Library &library);
void deleteBookOption(Library &library);
void deleteReaderOption(Library &library);
void searchBookOption(Library &library);
void displayBookOption(Library &library);
void addReaderOption(Library &library);
void manageBorrowedBookOption(Library &library);
void returnBookOption(Library &library);
void displayReaderOption(const Library &library);
void saveOption(Library &library);
void exitOption(Library &library);
void handleOption(Option option, Library &library);
int checkValidInput();

int main()
{
    Library library;

    cout << "Loading library data...\n";
    library.loadFromFile("books.txt", "readers.txt");
    cout << "Library data loaded.\n";

    while(running)
    {
        clearScreen();

        cout << "=== LIBRARY MANAGEMENT ===\n";
        cout << static_cast<int>(Option::ADD_BOOK) << ". Add a book\n";
        cout << static_cast<int>(Option::EDIT_BOOK) << ". Edit a book\n";
        cout << static_cast<int>(Option::DELETE_BOOK) << ". Delete a book\n";
        cout << static_cast<int>(Option::SEARCH_BOOK) << ". Search for a book\n";
        cout << static_cast<int>(Option::DISPLAY_BOOKS) << ". Display all books\n";
        cout << static_cast<int>(Option::ADD_READER) << ". Add a reader\n";
        cout << static_cast<int>(Option::DELETE_READER) << ". Delete a reader\n";
        cout << static_cast<int>(Option::MANAGE_BORROWED) << ". Borrow a book\n";
        cout << static_cast<int>(Option::RETURN_BOOK) << ". Return a book\n";
        cout << static_cast<int>(Option::DISPLAY_READERS) << ". Display all readers\n";
        cout << static_cast<int>(Option::SAVE) << ". Save library data\n";
        cout << static_cast<int>(Option::EXIT) << ". Exit\n";

        int option = checkValidInput();

        if (option >= static_cast<int>(Option::EXIT) && option <= static_cast<int>(Option::SAVE))
        {
            handleOption(static_cast<Option>(option), library);
        }
        else
        {
            cout << "Invalid option! Please choose between " << static_cast<int>(Option::EXIT) << " and " << static_cast<int>(Option::SAVE) << '\n';
            wPause();
        }
    }

    return 0;
}

// Pause and wait for user input
void wPause()
{
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    cout << "Press Enter to continue...";
    cin.get();
}

// Clear the screen
void clearScreen()
{
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {0, 0};
    DWORD count;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    FillConsoleOutputCharacter(hStdOut, ' ', csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
    SetConsoleCursorPosition(hStdOut, coord);
}

// Add a new book to the library
void addBookOption(Library &library)
{
    clearScreen();

    cout << "=== ADD BOOK ===\n";

    string bookID;
    cout << "Id: ";
    cin >> bookID;
    
    if(library.isBookIdExist(bookID))
    {
        cout << "Error: Book ID already exists!\n";
        wPause();
        return;
    }

    string bookTitle;
    cout << "Title: ";
    cin.ignore();
    getline(cin, bookTitle);

    string bookAuthor;
    cout << "Author: ";
    getline(cin, bookAuthor);

    string bookGenre;
    cout << "Genre: ";
    getline(cin, bookGenre);

    int year;
    cout << "Year: ";
    cin >> year;

    if(year < 0)
    {
        cout << "Error: Invalid year!\n";
        wPause();
        return;
    }

    int quantity;
    cout << "Quantity: ";
    cin >> quantity;

    if(quantity < 0)
    {
        cout << "Error: Invalid quantity!\n";
        wPause();
        return;
    }

    bool isAvailable = true;

    library.appendBook(Book(bookID, bookTitle, bookAuthor, bookGenre, year, quantity, isAvailable));
    cout << "Book added!\n";

    wPause();
}

// Edit an existing book in the library
void editBookOption(Library &library)
{
    clearScreen();

    cout << "=== EDIT BOOK ===\n";

    string bookID;
    cout << "Enter book's ID to edit: ";
    cin >> bookID;
    
    if(!library.isBookIdExist(bookID))
    {
        cout << "Error: Book ID not found!\n";
        wPause();
        return;
    }

    library.displayBookDetail(bookID);

    string newTitle;
    cout << "New title: ";
    cin.ignore();
    getline(cin, newTitle);

    string newAuthor;
    cout << "New author: ";
    getline(cin, newAuthor);

    string newGenre;
    cout << "New genre: ";
    getline(cin, newGenre);

    int newYear;
    cout << "New year: ";
    cin >> newYear;

    if(newYear < 0)
    {
        cout << "Error: Invalid year!\n";
        wPause();
        return;
    }

    int newQuantity;
    cout << "New quantity: ";
    cin >> newQuantity;

    if(newQuantity < 0)
    {
        cout << "Error: Invalid quantity!\n";
        wPause();
        return;
    }

    library.editBookDetail(bookID, newTitle, newAuthor, newGenre, newYear, newQuantity);
    cout << "Book edited!\n";

    wPause();
}

// Delete a book from the library
void deleteBookOption(Library &library)
{
    clearScreen();

    cout << "=== DELETE BOOK ===\n";

    string id;
    cout <<"Enter book's ID to delete: ";
    cin >> id;

    if(!library.deleteBook(id))
    {
        cout << "Error: Book ID not found!\n";
        wPause();
        return;
    }

    cout << "Book deleted!\n";

    wPause();
}

// Delete a reader from the library
void deleteReaderOption(Library &library)
{
    clearScreen();

    cout << "=== DELETE READER ===\n";

    string id;
    cout <<"Enter reader's ID to delete: ";
    cin >> id;

    if(!library.deleteReader(id))
    {
        cout << "Error: Reader ID not found!\n";
        wPause();
        return;
    }
    
    cout << "Reader deleted!\n";

    wPause();
}

// Search for a book in the library
void searchBookOption(Library &library)
{
    clearScreen();

    cout << "=== SEARCH BOOK ===\n";
    cout << "1. Search by Title\n";
    cout << "2. Search by Genre\n";
    cout << "3. Search by ID\n";
    
    int option = checkValidInput();

    if(option < 1 || option > 3)
    {
        cout << "Invalid option! Please choose between 1 and 3.\n";
        wPause();
        return;
    }

    switch(option)
    {
        case 1:
            {
                string searchTitle;
                cout << "Enter title to search: ";
                cin.ignore();
                getline(cin, searchTitle);
                library.displaySearchResult(library.findBookByTitle(searchTitle));
                break;
            }
        case 2:
            {
                string searchGenre;
                cout << "Enter genre to search: ";
                cin.ignore();
                getline(cin, searchGenre);
                library.displaySearchResult(library.findBookByGenre(searchGenre));
                break;
            }
        case 3:
            {
                string searchBookID;
                cout << "Enter book ID to search: ";
                cin >> searchBookID;
                library.displaySearchResult(library.findBookByID(searchBookID));
                break;
            }
        
        default:
            cout << "Invalid option!";
            break;
    }
    cout << "Press Enter to continue...";
    cin.get();
}

// Display all books in the library
void displayBookOption(Library &library)
{
    clearScreen();

    cout << "=== DISPLAY BOOK ===\n";

    library.displayBooks();

    wPause();
}

// Add a new reader to the library
void addReaderOption(Library &library)
{
    clearScreen();

    cout << "=== ADD READER ===\n";

    string readerID;
    cout << "ID: ";
    cin >> readerID;
    cin.ignore();

    if(library.isReaderIdExist(readerID))
    {
        cout << "Error: Reader ID already exists!\n";
        wPause();
        return;
    }

    string readerName;
    cout << "Name: ";
    getline(cin, readerName);

    std::vector<string> emptyBorrowedBook;

    library.appendReader(Reader(readerID, readerName, emptyBorrowedBook));
    cout << "Reader added!\n";

    cout << "Press Enter to continue...";
    cin.get();
}

// Manage borrowed books for a reader
void manageBorrowedBookOption(Library &library)
{
    clearScreen();

    cout << "=== BORROW BOOK ===\n";

    string bookID;
    cout << "Book ID: ";
    cin >> bookID;

    string readerID;
    cout << "Reader ID: ";
    cin >> readerID;

    if(!library.borrowBook(bookID, readerID))
    {
        wPause();
        return;
    }

    cout << "Book borrowed!\n";

    wPause();
}

// Return a borrowed book to the library
void returnBookOption(Library &library)
{
    clearScreen();

    cout << "=== RETURN BOOK ===\n";

    string bookID;
    cout << "Book ID: ";
    cin >> bookID;

    string readerID;
    cout << "Reader ID: ";
    cin >> readerID;

    if(!library.returnBook(bookID, readerID))
    {
        wPause();
        return;
    }

    cout << "Book returned!\n";

    wPause();
}

// Display all readers in the library
void displayReaderOption(const Library &library)
{
    clearScreen();

    cout << "=== DISPLAY READER ===\n";

    library.displayReaders();

    wPause();
}

// Save library data to files
void saveOption(Library &library)
{
    cout << "Saving library data...\n";
    library.saveToFile("books.txt", "readers.txt");
    cout << "Library data saved!\n";
    wPause();
}

// Exit the program and save library data
void exitOption(Library &library)
{
    cout << "Exiting...\n";
    library.saveToFile("books.txt", "readers.txt");
    running = false;
    cout << "Thank you for using!\n";
}

// Handle user option
void handleOption(Option option, Library &library)
{
    switch (option) 
    {
        case Option::ADD_BOOK:
            addBookOption(library);
            break;
        case Option::EDIT_BOOK:
            editBookOption(library);
            break;
        case Option::DELETE_BOOK:
            deleteBookOption(library);
            break;
        case Option::SEARCH_BOOK:
            searchBookOption(library);
            break;
        case Option::DISPLAY_BOOKS:
            displayBookOption(library);
            break;
        case Option::ADD_READER:
            addReaderOption(library);
            break;
        case Option::DELETE_READER:
            deleteReaderOption(library);
            break;
        case Option::MANAGE_BORROWED:
            manageBorrowedBookOption(library);
            break;
        case Option::RETURN_BOOK:
            returnBookOption(library);
            break;
        case Option::DISPLAY_READERS:
            displayReaderOption(library);
            break;
        case Option::SAVE:
            saveOption(library);
            break;
        case Option::EXIT:
            exitOption(library);
            break;
        default:
            break;
    }
}

// Check if the user input is a valid option
int checkValidInput() {
    int option = 0;
    string input;
    bool validInput = false;

    while (!validInput)
    {
        cout << "Enter your option: ";
        cin >> input;

        try
        {
            if (input.empty())
            {
                throw std::invalid_argument("Empty input.");
            }
            
            if (!std::all_of(input.begin(), input.end(), ::isdigit))
            {
                throw std::invalid_argument("Invalid input! Please enter a number.");
            }
            
            option = std::stoi(input);
            validInput = true;
        }
        catch (const std::invalid_argument &e)
        {
            cout << "Error: " << e.what() << ". Please try again.\n";
        }
        catch (const std::out_of_range &e)
        {
            cout << "Error: Number out of range. Please try again.\n";
        }
    }
    return option;
}