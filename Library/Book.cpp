#pragma once
#include <iostream>

using std::string;

class Book
{
    private:
        string bookID;
        string title;
        string author;
        string genre;
        int year;
        int quantity;
        bool isAvailable;
    public:
        Book(){};

        Book(const string &bookID, const string &title, const string &author, const string &genre, const int year, const int quantity, const bool isAvailable):
            bookID(bookID), title(title), author(author), genre(genre), year(year), quantity(quantity), isAvailable(isAvailable) {};

        void setId(const string &bookID)
        {
            this->bookID = bookID;
        }

        void setTitle(const string &title)
        {
            this->title = title;
        }

        void setAuthor(const string &author)
        {
            this->author = author;
        }

        void setGenre(const string &genre)
        {
            this->genre = genre;
        }

        void setYear(const int &year)
        {
            this->year = year;
        }

        void setQuantity(const int &quantity)
        {
            this->quantity = quantity;
        }

        void setIsAvailable(bool &isAvailable)
        {
            this->isAvailable = isAvailable;
        }

        string getId() const
        {
            return bookID;
        }

        string getTitle() const
        {
            return title;
        }

        string getAuthor() const
        {
            return author;
        }

        string getGenre() const
        {
            return genre;
        }

        int getYear() const
        {
            return year;
        }

        int getQuantity() const
        {
            return quantity;
        }

        bool getIsAvailable() const
        {
            return isAvailable;
        }
};