#include <algorithm>
#include <iomanip>
#include <fstream>
#include <sstream>
#include "Book.cpp"
#include "Reader.cpp"

using std::string;
using std::cout;

class Library
{
    private:
        std::vector<Book> books;
        std::vector<Reader> readers;

        //Find reader id
        Reader* findReader(const string &readerID)
        {
            auto it = std::find_if(readers.begin(), readers.end(), [&readerID](Reader &reader)
            {
                return reader.getId() == readerID;
            });

            if(it != readers.end())
            {
                return &(*it);
            }
            return nullptr;
        }

        //Find book by id
        Book* findBook(const string &bookID)
        {
            auto it = std::find_if(books.begin(), books.end(), [&bookID](Book &book)
            {
                return book.getId() == bookID;
            });

            if(it != books.end())
            {
                return &(*it);
            }
            return nullptr;
        }

    public:
        Library(){};

        Library(const std::vector<Book> &books, const std::vector<Reader> &readers)
            : books(books), readers(readers) {};

        //Check existing book ID
        bool isBookIdExist(const string &bookID)
        {
            return findBook(bookID) != nullptr;
        }

        //Check existing reader ID
        bool isReaderIdExist(const string &readerID)
        {
            return findReader(readerID) != nullptr;
        }

        //Add book
        void appendBook(const Book &book)
        {
            books.push_back(book);
        }
        
        //Add reader
        void appendReader(const Reader &reader)
        {
            readers.push_back(reader);
        }

        //Edit book title
        bool editBookTitle(const string &bookID, string &newTitle)
        {
            Book* book = findBook(bookID);

            if(book)
            {
                book->setTitle(newTitle);
                return true;
            }  
            return false;
        }

        //Edit book author
        bool editBookAuthor(const string &bookID, string &newAuthor)
        {
            Book* book = findBook(bookID);

            if(book)
            {
                book->setAuthor(newAuthor);
                return true;
            }
            return false;
        }

        //Edit book genre
        bool editBookGenre(const string &bookID, string &newGenre)
        {
            Book* book = findBook(bookID);

            if(book)
            {
                book->setGenre(newGenre);
                return true;
            }
            return false;
        }

        //Edit book year
        bool editBookYear(const string &bookID, int &newYear)
        {
            Book* book = findBook(bookID);

            if(book)
            {
                book->setYear(newYear);
                return true;
            }
            return false;
        }

        //Edit a book in detail
        bool editBookDetail(const string &bookID, const string &newTitle, const string &newAuthor, const string &newGenre, const int &newYear, const int &newQuantity)
        {
            Book *book = findBook(bookID);

            if(book)
            {
                book->setTitle(newTitle);
                book->setAuthor(newAuthor);
                book->setGenre(newGenre);
                book->setYear(newYear);
                book->setQuantity(newQuantity);
                return true;
            }
            return false;
        }

        //Display a book in detail
        void displayBookDetail(const string &bookID)
        {
            Book *book = findBook(bookID);

            if(book)
            {
                cout << "=== CURRENT BOOK STATUS ===\n";
                cout << "Book ID: " << book->getId() << '\n';
                cout << "Title: " << book->getTitle() << '\n';
                cout << "Author: " << book->getAuthor() << '\n';
                cout <<"Genre: " << book->getGenre() << '\n';
                cout << "Year: " << book->getYear() << '\n';
                cout << "Quantity: " << book->getQuantity() << '\n';
                cout << "Available: " << (book->getIsAvailable() ? "Yes" : "No") << '\n';
                cout << "---------------------------\n";
            } 
            else 
            {
                cout << "Error: Book not found.\n";
            }
        }

        //Edit reader name
        bool editReaderName(const string &readerID, string &newName)
        {
            Reader *reader = findReader(readerID);

            if(reader)
            {
                reader->setName(newName);
                return true;
            }
            return false;
        }

        //Borrow a book
        bool borrowBook(const string &bookID, const string &readerID)
        {
            Reader* reader = findReader(readerID);
            Book* book = findBook(bookID);

            if(!reader)
            {
                cout << "Error: Reader ID not found.\n";
                return false;
            }

            if(!book)
            {
                cout << "Error: Book ID not found.\n";
                return false;
            }

            if(!book->getIsAvailable())
            {
                cout << "Error: Book is not available for borrowing.\n";
                return false;
            }

            
            book->setQuantity(book->getQuantity() - 1);

            if(book->getQuantity() == 0)
            {
                bool available = false;
                book->setIsAvailable(available);
            }

            reader->appendBorrowedBook(bookID);

            return true;
        }

        //Return a book
        bool returnBook(const string &bookID, const string &readerID)
        {
            Reader* reader = findReader(readerID);
            Book* book = findBook(bookID);

            if(!reader)
            {
                cout << "Error: Reader ID not found.\n";
                return false;
            }

            if(!book)
            {
                cout << "Error: Book ID not found.\n";
                return false;
            }

            if(!reader->hasBorrowedBook(bookID))
            {
                cout << "Error: Book ID not found in reader's borrowed books.\n";
                return false;
            }

            book->setQuantity(book->getQuantity() + 1);

            if(book->getQuantity() > 0)
            {
                bool available = true;
                book->setIsAvailable(available);
            }

            reader->deleteBorrowedBooks(bookID);
            
            return true;
        }

        //Display borrowed books
        void displayBorrowedBooks(const string &readerID)
        {
            Reader *reader = findReader(readerID);

            if(!reader)
            {
                cout << "Reader not found!\n";
                return;
            }

            if(reader->getBorrowedBooks().empty())
            {
                cout << "No book is borrowed by this reader!\n";
                return;
            }
            
            cout << "Borrowed books for reader " << reader->getName() << ":\n";
            for(const auto &bookID: reader->getBorrowedBooks())
            {
                Book *book = findBook(bookID);

                if(book)
                {
                    cout << "Book ID: " << book->getId() << '\n';
                    cout << "Title: " << book->getTitle() << '\n';
                    cout << "Author: " << book->getAuthor() << '\n';
                    cout << "--------------------------\n";
                }
            }
        }

        void displayBooks() const
        {
            if(!books.empty())
            {
                cout << "=========================================================================================================================\n";
                cout << "| Book ID | Title                         | Author                       | Genre          | Year | Quantity | Available |\n";
                cout << "=========================================================================================================================\n";
                for(const auto &book: books)
                {
                    cout << "| " << std::setw(7) << book.getId() << " | "
                         << std::setw(29) << book.getTitle() << " | "
                         << std::setw(28) << book.getAuthor() << " | "
                         << std::setw(14) << book.getGenre() << " | "
                         << std::setw(4) << book.getYear() << " | "
                         << std::setw(8) << book.getQuantity() << " | "
                         << std::setw(9) << (book.getIsAvailable() ? "Yes" : "No") << " |\n";
                }
                cout << "========================================================================================================================\n";
            }
            else
            {
                cout << "The library is empty!\n";
            }
        }

        void displayReaders() const
        {
            if(!readers.empty())
            {
                cout << "=============================================================\n";
                cout << "| Reader ID | Name                         | Books Borrowed |\n";
                cout << "=============================================================\n";
                for(const auto &reader: readers)
                {
                    cout << "| " << std::setw(9) << reader.getId() << " | "
                         << std::setw(28) << reader.getName() << " | "
                         << std::setw(14) << reader.getTotalBorrowedBooks() << " |\n";
                }
                cout << "=============================================================\n";
            }
            else
            {
                cout << "No readers found!\n";
            }
        }

        //Check if the book is borrowed
        bool isBorrowedBook(const string &bookID)
        {
            for (auto &reader : readers)
            {
                if (reader.hasBorrowedBook(bookID))
                {
                    return true;
                }
            }
            return false;
        }

        bool isBorrowedBook(const string &bookID, const string &readerID)
        {
            Reader *reader = findReader(readerID);

            if(!reader)
            {
                return false;
            }

            if(reader->hasBorrowedBook(bookID))
            {
                return true;
            }
            return false;
        }

        //Get total of books borrowed by reader
        int getReaderBorrowedBook(const string &readerID)
        {
            Reader *reader = findReader(readerID);

            if(reader)
            {
                return reader->getBorrowedBooks().size();
            }
                return 0;
        }

        //Delete book
        bool deleteBook(const string &bookID)
        {
            auto it = std::find_if(books.begin(), books.end(), [&bookID](Book &book)
            {
                return book.getId() == bookID;
            });

            if(it != books.end())
            {
                books.erase(it);
                return true;
            }
            return false;
        }

        //Delete reader
        bool deleteReader(const string &readerID)
        {
            auto it = std::find_if(readers.begin(), readers.end(), [&readerID](Reader &reader)
            {
                return reader.getId() == readerID;
            });

            if(it != readers.end())
            {
                readers.erase(it);
                return true;
            }
            return false;
        }

        //Find book by title
        std::vector<Book*> findBookByTitle(const string &findTitle)
        {
            std::vector<Book*> foundBooks;

            for(auto &book: books)
            {
                if(book.getTitle() == findTitle)
                {
                    foundBooks.push_back(&book);
                }
            }
            return foundBooks;
        }

        //Find book by genre
        std::vector<Book*> findBookByGenre(const string &findGenre)
        {
            std::vector<Book*> foundBooks;

            for(auto &book: books)
            {
                if(book.getGenre() == findGenre)
                {
                    foundBooks.push_back(&book);
                }
            }
            return foundBooks;
        }

        std::vector<Book*> findBookByID(const string &findBookID)
        {
            std::vector<Book*> foundBooks;
            Book* book = findBook(findBookID);

            if(book)
            {
                foundBooks.push_back(book);
            }
            return foundBooks;
        }

        //Display search result
        void displaySearchResult(const std::vector<Book*> &foundBooks)
        {
            if(foundBooks.empty())
            {
                cout << "No books found matching your criteria.\n";
                return;
            }

            cout << "Found: " << foundBooks.size() << " books\n";
            for(const auto &book: foundBooks)
            {
                cout << "--------------------------\n";
                cout << "Book ID: " << book->getId() << '\n';
                cout << "Title: " << book->getTitle() << '\n';
                cout << "Author: " << book->getAuthor() << '\n';
                cout << "Genre: " << book->getGenre() << '\n';
                cout << "Year: "<< book->getYear() << '\n';
                cout << "Available: " << (book->getIsAvailable() ? "Yes" : "No") << '\n';
            }
        }

        void saveToFile(const char *bookFileName, const char *readerFileName)
        {
            std::ofstream bookFile(bookFileName);
            if (!bookFile.is_open())
            {
                cout << "Error: Failed to open book file for writing.\n";
                return;
            }

            for(auto &book : books)
            {
                bookFile << book.getId() << "|";
                bookFile << book.getTitle() << "|";
                bookFile << book.getAuthor() << "|";
                bookFile << book.getGenre() << "|";
                bookFile << book.getYear() << "|";
                bookFile << book.getQuantity() << "|";
                bookFile << (book.getIsAvailable() ? "1" : "0") << "\n";
            }
            bookFile.close();

            std::ofstream readerFile(readerFileName);
            if (!readerFile.is_open())
            {
                cout << "Error: Failed to open reader file for writing.\n";
                return;
            }

            for(auto &reader : readers)
            {
                readerFile << reader.getId() << "|"
                           << reader.getName() << "\n";

                if (!reader.getBorrowedBooks().empty())
                {
                    for(size_t i = 0; i < reader.getBorrowedBooks().size() - 1; ++i)
                    {
                        readerFile << reader.getBorrowedBooks()[i] << "|";
                    }
                    readerFile << reader.getBorrowedBooks().back();
                }
                
                readerFile << "\n";
            }
            readerFile.close();
        }

        void loadFromFile(const char *bookFileName, const char *readerFileName)
        {
            std::ifstream inBookFile(bookFileName);
            if (!inBookFile.is_open())
            {
                cout << "Error: Failed to open book file for reading.\n";
                return;
            }

            string line;
            while(getline(inBookFile, line))
            {
                std::stringstream ss(line);
                string bookID, title, author, genre, yearStr, quantityStr, availableStr;
                
                try
                {
                    getline(ss, bookID, '|');
                    getline(ss, title, '|');
                    getline(ss, author, '|');
                    getline(ss, genre, '|');
                    getline(ss, yearStr, '|');
                    getline(ss, quantityStr, '|');
                    getline(ss, availableStr, '|');
                    
                    int year = stoi(yearStr);
                    int quantity = stoi(quantityStr);
                    bool isAvailable = (availableStr == "1");
                    
                    books.push_back(Book(bookID, title, author, genre, year, quantity, isAvailable));
                }
                catch (const std::invalid_argument &e)
                {
                    cout << "Error: Invalid argument while parsing book file. Line: " << line << "\n";
                }
                catch (const std::out_of_range &e)
                {
                    cout << "Error: Out of range while parsing book file. Line: " << line << "\n";
                }
            }
            inBookFile.close();

            std::ifstream inReaderFile(readerFileName);
            if (!inReaderFile.is_open())
            {
                cout << "Error: Failed to open reader file for reading.\n";
                return;
            }

            while(getline(inReaderFile, line))
            {
                std::stringstream ss(line);
                string readerID, name;
                try
                {
                    getline(ss, readerID, '|');
                    getline(ss, name, '\n');

                    std::vector<string> borrowedBooks;
                    if(getline(inReaderFile, line))
                    {
                        std::stringstream ssBooks(line);
                        string bookID;
                        while(getline(ssBooks, bookID, '|'))
                        {
                            borrowedBooks.push_back(bookID);
                        }
                    }

                    readers.push_back(Reader(readerID, name, borrowedBooks));
                }
                catch (const std::invalid_argument &e)
                {
                    cout << "Error: Invalid argument while parsing reader file. Line: " << line << "\n";
                }
                catch (const std::out_of_range &e)
                {
                    cout << "Error: Out of range while parsing reader file. Line: " << line << "\n";
                }
            }
            inReaderFile.close();
        }
};