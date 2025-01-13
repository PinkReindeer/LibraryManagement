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

        // Find reader by ID
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

        // Find book by ID
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

        // Check if book ID exists
        bool isBookIdExist(const string &bookID)
        {
            return findBook(bookID) != nullptr;
        }

        // Check if reader ID exists
        bool isReaderIdExist(const string &readerID)
        {
            return findReader(readerID) != nullptr;
        }

        // Add a book to the library
        void appendBook(const Book &book)
        {
            cout << "Appending book: " << book.getTitle() << '\n';
            books.push_back(book);
        }
        
        // Add a reader to the library
        void appendReader(const Reader &reader)
        {
            cout << "Appending reader: " << reader.getName() << '\n';
            readers.push_back(reader);
        }

        // Edit book title
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

        // Edit book author
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

        // Edit book genre
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

        // Edit book year
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

        // Edit book details
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

                if (newQuantity > 0)
                {
                    bool available = true;
                    book->setIsAvailable(available);
                }

                return true;
            }
            return false;
        }

        // Display book details
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

        // Edit reader name
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

        // Borrow a book
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

        // Return a book
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

        // Display borrowed books
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

        // Display all books in the library
        void displayBooks() const
        {
            if(!books.empty())
            {
                size_t maxIdWidth = 5;
                size_t maxTitleWidth = 5;
                size_t maxAuthorWidth = 10;
                size_t maxGenreWidth = 8;
                size_t maxYearWidth = 4;
                size_t maxQuantityWidth = 5;
                size_t maxAvailableWidth = 8;

                for(const auto &book: books)
                {
                    maxIdWidth = (std::max)(maxIdWidth, book.getId().length());
                    maxTitleWidth = (std::max)(maxTitleWidth, book.getTitle().length());
                    maxAuthorWidth = (std::max)(maxAuthorWidth, book.getAuthor().length());
                    maxGenreWidth = (std::max)(maxGenreWidth, book.getGenre().length());
                }

                cout << std::string(maxIdWidth + maxTitleWidth + maxAuthorWidth + maxGenreWidth + maxYearWidth + maxQuantityWidth + maxAvailableWidth + 22, '=') << '\n';
                cout << "| " << std::setw(maxIdWidth) << "Book ID" << " | "
                     << std::setw(maxTitleWidth) << "Title" << " | "
                     << std::setw(maxAuthorWidth) << "Author" << " | "
                     << std::setw(maxGenreWidth) << "Genre" << " | "
                     << std::setw(maxYearWidth) << "Year" << " | "
                     << std::setw(maxQuantityWidth) << "Quantity" << " | "
                     << std::setw(maxAvailableWidth) << "Available" << " |\n";
                cout << std::string(maxIdWidth + maxTitleWidth + maxAuthorWidth + maxGenreWidth + maxYearWidth + maxQuantityWidth + maxAvailableWidth + 22, '=') << '\n';

                for(const auto &book: books)
                {
                    cout << "| " << std::setw(maxIdWidth) << book.getId() << " | "
                         << std::setw(maxTitleWidth) << book.getTitle() << " | "
                         << std::setw(maxAuthorWidth) << book.getAuthor() << " | "
                         << std::setw(maxGenreWidth) << book.getGenre() << " | "
                         << std::setw(maxYearWidth) << book.getYear() << " | "
                         << std::setw(maxQuantityWidth) << book.getQuantity() << " | "
                         << std::setw(maxAvailableWidth) << (book.getIsAvailable() ? "Yes" : "No") << " |\n";
                }
                cout << std::string(maxIdWidth + maxTitleWidth + maxAuthorWidth + maxGenreWidth + maxYearWidth + maxQuantityWidth + maxAvailableWidth + 22, '=') << '\n';
            }
            else
            {
                cout << "The library is empty!\n";
            }
        }

        // Display all readers in the library
        void displayReaders() const
        {
            if(!readers.empty())
            {
                size_t maxIdWidth = 5;
                size_t maxNameWidth = 10;
                size_t maxBorrowedWidth = 5;

                for(const auto &reader: readers)
                {
                    maxIdWidth = (std::max)(maxIdWidth, reader.getId().length());
                    maxNameWidth = (std::max)(maxNameWidth, reader.getName().length());
                }

                cout << std::string(maxIdWidth + maxNameWidth + maxBorrowedWidth + 10, '=') << '\n';
                cout << "| " << std::setw(maxIdWidth) << "Reader ID" << " | "
                     << std::setw(maxNameWidth) << "Name" << " | "
                     << std::setw(maxBorrowedWidth) << "Books Borrowed" << " |\n";
                cout << std::string(maxIdWidth + maxNameWidth + maxBorrowedWidth + 10, '=') << '\n';

                for(const auto &reader: readers)
                {
                    cout << "| " << std::setw(maxIdWidth) << reader.getId() << " | "
                         << std::setw(maxNameWidth) << reader.getName() << " | "
                         << std::setw(maxBorrowedWidth) << reader.getTotalBorrowedBooks() << " |\n";
                }
                cout << std::string(maxIdWidth + maxNameWidth + maxBorrowedWidth + 10, '=') << '\n';
            }
            else
            {
                cout << "No readers found!\n";
            }
        }

        // Check if the book is borrowed by any reader
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

        // Check if the book is borrowed by a reader
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

        // Get total number of books borrowed by a reader
        int getReaderBorrowedBook(const string &readerID)
        {
            Reader *reader = findReader(readerID);

            if(reader)
            {
                return reader->getBorrowedBooks().size();
            }
                return 0;
        }

        // Delete a book from the library
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

        // Delete a reader from the library
        bool deleteReader(const string &readerID)
        {
            auto it = std::find_if(readers.begin(), readers.end(), [&readerID](Reader &reader)
            {
                return reader.getId() == readerID;
            });

            if(it != readers.end())
            {
                // Return all borrowed books
                for (const auto &bookID : it->getBorrowedBooks())
                {
                    Book* book = findBook(bookID);
                    if (book)
                    {
                        book->setQuantity(book->getQuantity() + 1);
                        if (book->getQuantity() > 0)
                        {
                            bool available = true;
                            book->setIsAvailable(available);
                        }
                    }
                }

                readers.erase(it);
                return true;
            }
            return false;
        }

        // Find books by title
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

        // Find books by genre
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

        // Find books by ID
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

        // Display search results
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

        // Save library data to file
        void saveToFile(const char *bookFileName, const char *readerFileName)
        {
            std::ofstream bookFile(bookFileName, std::ios::binary);
            if (!bookFile.is_open())
            {
                cout << "Error: Failed to open book file for writing.\n";
                return;
            }

            size_t bookCount = books.size();
            bookFile.write(reinterpret_cast<const char*>(&bookCount), sizeof(bookCount));
            cout << "Saving " << bookCount << " books to file.\n";

            for(const auto &book : books)
            {
                size_t idSize = book.getId().size();
                bookFile.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
                bookFile.write(book.getId().c_str(), idSize);

                size_t titleSize = book.getTitle().size();
                bookFile.write(reinterpret_cast<const char*>(&titleSize), sizeof(titleSize));
                bookFile.write(book.getTitle().c_str(), titleSize);

                size_t authorSize = book.getAuthor().size();
                bookFile.write(reinterpret_cast<const char*>(&authorSize), sizeof(authorSize));
                bookFile.write(book.getAuthor().c_str(), authorSize);

                size_t genreSize = book.getGenre().size();
                bookFile.write(reinterpret_cast<const char*>(&genreSize), sizeof(genreSize));
                bookFile.write(book.getGenre().c_str(), genreSize);

                int year = book.getYear();
                bookFile.write(reinterpret_cast<const char*>(&year), sizeof(year));

                int quantity = book.getQuantity();
                bookFile.write(reinterpret_cast<const char*>(&quantity), sizeof(quantity));

                bool isAvailable = book.getIsAvailable();
                bookFile.write(reinterpret_cast<const char*>(&isAvailable), sizeof(isAvailable));
            }
            bookFile.close();
            cout << "Books saved successfully.\n";

            std::ofstream readerFile(readerFileName, std::ios::binary);
            if (!readerFile.is_open())
            {
                cout << "Error: Failed to open reader file for writing.\n";
                return;
            }

            size_t readerCount = readers.size();
            readerFile.write(reinterpret_cast<const char*>(&readerCount), sizeof(readerCount));
            cout << "Saving " << readerCount << " readers to file.\n";

            for(const auto &reader : readers)
            {
                size_t idSize = reader.getId().size();
                readerFile.write(reinterpret_cast<const char*>(&idSize), sizeof(idSize));
                readerFile.write(reader.getId().c_str(), idSize);

                size_t nameSize = reader.getName().size();
                readerFile.write(reinterpret_cast<const char*>(&nameSize), sizeof(nameSize));
                readerFile.write(reader.getName().c_str(), nameSize);

                size_t borrowedCount = reader.getBorrowedBooks().size();
                readerFile.write(reinterpret_cast<const char*>(&borrowedCount), sizeof(borrowedCount));

                for(const auto &bookID : reader.getBorrowedBooks())
                {
                    size_t bookIDSize = bookID.size();
                    readerFile.write(reinterpret_cast<const char*>(&bookIDSize), sizeof(bookIDSize));
                    readerFile.write(bookID.c_str(), bookIDSize);
                }
            }
            readerFile.close();
            cout << "Readers saved successfully.\n";
        }

        // Load library data from file
        void loadFromFile(const char *bookFileName, const char *readerFileName)
        {
            std::ifstream inBookFile(bookFileName, std::ios::binary);
            if (!inBookFile.is_open())
            {
                cout << "Error: Failed to open book file for reading.\n";
                return;
            }

            size_t bookCount;
            inBookFile.read(reinterpret_cast<char*>(&bookCount), sizeof(bookCount));
            cout << "Loading " << bookCount << " books from file.\n";

            for(size_t i = 0; i < bookCount; ++i)
            {
                size_t idSize;
                inBookFile.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
                string bookID(idSize, ' ');
                inBookFile.read(&bookID[0], idSize);

                size_t titleSize;
                inBookFile.read(reinterpret_cast<char*>(&titleSize), sizeof(titleSize));
                string title(titleSize, ' ');
                inBookFile.read(&title[0], titleSize);

                size_t authorSize;
                inBookFile.read(reinterpret_cast<char*>(&authorSize), sizeof(authorSize));
                string author(authorSize, ' ');
                inBookFile.read(&author[0], authorSize);

                size_t genreSize;
                inBookFile.read(reinterpret_cast<char*>(&genreSize), sizeof(genreSize));
                string genre(genreSize, ' ');
                inBookFile.read(&genre[0], genreSize);

                int year;
                inBookFile.read(reinterpret_cast<char*>(&year), sizeof(year));

                int quantity;
                inBookFile.read(reinterpret_cast<char*>(&quantity), sizeof(quantity));

                bool isAvailable;
                inBookFile.read(reinterpret_cast<char*>(&isAvailable), sizeof(isAvailable));

                books.push_back(Book(bookID, title, author, genre, year, quantity, isAvailable));
            }
            inBookFile.close();
            cout << "Books loaded successfully.\n";

            std::ifstream inReaderFile(readerFileName, std::ios::binary);
            if (!inReaderFile.is_open())
            {
                cout << "Error: Failed to open reader file for reading.\n";
                return;
            }

            size_t readerCount;
            inReaderFile.read(reinterpret_cast<char*>(&readerCount), sizeof(readerCount));
            cout << "Loading " << readerCount << " readers from file.\n";

            if (readerCount > 1000000)
            {
                cout << "Error: Reader count is too large, possible file corruption.\n";
                inReaderFile.close();
                return;
            }

            for(size_t i = 0; i < readerCount; ++i)
            {
                size_t idSize;
                inReaderFile.read(reinterpret_cast<char*>(&idSize), sizeof(idSize));
                string readerID(idSize, ' ');
                inReaderFile.read(&readerID[0], idSize);

                size_t nameSize;
                inReaderFile.read(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
                string name(nameSize, ' ');
                inReaderFile.read(&name[0], nameSize);

                size_t borrowedCount;
                inReaderFile.read(reinterpret_cast<char*>(&borrowedCount), sizeof(borrowedCount));

                std::vector<string> borrowedBooks;
                for(size_t j = 0; j < borrowedCount; ++j)
                {
                    size_t bookIDSize;
                    inReaderFile.read(reinterpret_cast<char*>(&bookIDSize), sizeof(bookIDSize));
                    string bookID(bookIDSize, ' ');
                    inReaderFile.read(&bookID[0], bookIDSize);
                    borrowedBooks.push_back(bookID);
                }

                readers.push_back(Reader(readerID, name, borrowedBooks));
            }
            inReaderFile.close();
            cout << "Readers loaded successfully.\n";
        }
};