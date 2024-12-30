#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using std::string;
using std::cout;

class Reader
{
    private:
        string readerID;
        string name;
        std::vector<string> borrowedBooks;
    public:
        Reader(){};

        Reader(const string &readerID, const string &name, const std::vector<string> &borrowedBooks)
            : readerID(readerID), name(name), borrowedBooks(borrowedBooks) {}

        void setId(const string &readerID)
        {
            this->readerID = readerID;
        }

        void setName(const string &name)
        {
            this->name = name;
        }

        void appendBorrowedBook(const string &bookID)
        {
            borrowedBooks.push_back(bookID);
        }
        
        bool deleteBorrowedBooks(const string &bookID)
        {
            auto it = std::find(borrowedBooks.begin(), borrowedBooks.end(), bookID);

            if(it != borrowedBooks.end())
            {
                borrowedBooks.erase(it);
                return true;
            }
            cout << "Error: Book ID not found in borrowed books.\n";
            return false;
        }

        const std::vector<string> &getBorrowedBooks() const
        {
            return borrowedBooks;
        }

        bool hasBorrowedBook(const string &bookID)
        {
            return std::find(borrowedBooks.begin(), borrowedBooks.end(), bookID) != borrowedBooks.end();
        }

        const int getTotalBorrowedBooks() const
        {
            return borrowedBooks.size();
        }

        string getId() const
        {
            return readerID;
        }

        string getName() const
        {
            return name;
        }
};