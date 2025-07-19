#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>

class Book {
private:
    int id;
    std::string title;
    std::string author;
    double price;
    int quantity;

public:
    Book();
    Book(int bookId, const std::string &bookTitle, const std::string &bookAuthor, double bookPrice, int bookQuantity);
    
    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getAuthor() const;
    double getPrice() const;
    int getQuantity() const;
    
    // Setters
    void setId(int bookId);
    void setTitle(const std::string &bookTitle);
    void setAuthor(const std::string &bookAuthor);
    void setPrice(double bookPrice);
    void setQuantity(int bookQuantity);
    
    // Display and update methods
    void display() const;
    void updateDetails();
    void updateQuantity(int newQuantity);
};

// Book management functions
void addBook();
void updateBook();
void deleteBook();
void viewAllBooks();
std::vector<Book> loadBooks();
void saveBooks(const std::vector<Book>& books);
Book* findBookById(std::vector<Book>& books, int id);
int generateNewBookId();

#endif
