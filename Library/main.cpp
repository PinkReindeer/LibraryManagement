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

void wPause()
{
    cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    cout << "Press Enter to continue...";
    cin.get();
}

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

void searchBookOption(Library &library)
{
    clearScreen();

    cout << "=== SEARCH BOOK ===\n";
    cout << "1. Search by Title\n";
    cout << "2. Search by Genre\n";
    cout << "3. Search by ID\n";
    cout << "Choose your option: ";

    string option;
    cin >> option;

    switch(std::stoi(option))
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
    wPause();
}

void displayBookOption(Library &library)
{
    clearScreen();

    cout << "=== DISPLAY BOOK ===\n";

    library.displayBooks();

    wPause();
}

void addReaderOption(Library &library)
{
    clearScreen();

    cout << "=== ADD READER ===\n";

    string readerID;
    cout << "ID: ";
    cin >> readerID;

    if(library.isReaderIdExist(readerID))
    {
        cout << "Error: Reader ID already exists!\n";
        wPause();
        return;
    }

    string readerName;
    cout << "Name: ";
    cin.ignore();
    getline(cin,readerName);

    std::vector<string> emptyBorrowedBook;

    library.appendReader(Reader(readerID, readerName, emptyBorrowedBook));
    cout << "Reader added!\n";

    wPause();
}

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

void displayReaderOption(const Library &library)
{
    clearScreen();

    cout << "=== DISPLAY READER ===\n";

    library.displayReaders();

    wPause();
}

void saveOption(Library &library)
{
    library.saveToFile("books.txt", "readers.txt");
    cout << "Library data saved!\n";
    wPause();
}

void exitOption()
{
    cout << "Thank you for using!\n";
    running = false;
}

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
            exitOption();
            break;
        default:
            break;
    }
    if (option == Option::EXIT)
    {
        library.saveToFile("books.txt", "readers.txt");
    }
}

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

int main()
{
    Library library;

    library.loadFromFile("books.txt", "readers.txt");

    while(running)
    {
        clearScreen();

        cout << "=== LIBRARY MANAGEMENT ===\n";
        cout << static_cast<int>(Option::ADD_BOOK) <<". Add a book.\n";
        cout << static_cast<int>(Option::EDIT_BOOK) <<". Edit book.\n";
        cout << static_cast<int>(Option::DELETE_BOOK) << ". Delete book.\n";
        cout << static_cast<int>(Option::SEARCH_BOOK) << ". Find book.\n";
        cout << static_cast<int>(Option::DISPLAY_BOOKS) << ". Display all books.\n";
        cout << static_cast<int>(Option::ADD_READER) << ". Add reader.\n";
        cout << static_cast<int>(Option::DELETE_READER) << ". Delete reader.\n";
        cout << static_cast<int>(Option::MANAGE_BORROWED) << ". Manage borrowed book.\n";
        cout << static_cast<int>(Option::RETURN_BOOK) << ". Return book.\n";
        cout << static_cast<int>(Option::DISPLAY_READERS) << ". Display all readers.\n";
        cout << static_cast<int>(Option::SAVE) << ". Save.\n";
        cout << static_cast<int>(Option::EXIT) << ". Exit.\n";

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