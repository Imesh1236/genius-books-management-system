#include "Book.h"
#include "DataHandler.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <algorithm>

// Book class implementation
Book::Book() : id(0), title(""), author(""), price(0.0), quantity(0) {}

Book::Book(int bookId, const std::string &bookTitle, const std::string &bookAuthor, double bookPrice, int bookQuantity)
    : id(bookId), title(bookTitle), author(bookAuthor), price(bookPrice), quantity(bookQuantity) {}

// Getters
int Book::getId() const { return id; }
std::string Book::getTitle() const { return title; }
std::string Book::getAuthor() const { return author; }
double Book::getPrice() const { return price; }
int Book::getQuantity() const { return quantity; }

// Setters
void Book::setId(int bookId) { id = bookId; }
void Book::setTitle(const std::string &bookTitle) { title = bookTitle; }
void Book::setAuthor(const std::string &bookAuthor) { author = bookAuthor; }
void Book::setPrice(double bookPrice) { price = bookPrice; }
void Book::setQuantity(int bookQuantity) { quantity = bookQuantity; }

void Book::display() const {
    std::cout << std::left << std::setw(5) << id
              << std::setw(25) << title.substr(0, 24)
              << std::setw(20) << author.substr(0, 19)
              << std::setw(10) << std::fixed << std::setprecision(2) << price
              << std::setw(8) << quantity << std::endl;
}

void Book::updateDetails() {
    std::string input;
    
    std::cout << "\nCurrent Details:" << std::endl;
    std::cout << "Title: " << title << std::endl;
    std::cout << "Author: " << author << std::endl;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << price << std::endl;
    std::cout << "Quantity: " << quantity << std::endl;
    
    std::cout << "\nEnter new details (press Enter to keep current value):" << std::endl;
    
    std::cout << "New Title: ";
    std::cin.ignore();
    std::getline(std::cin, input);
    if (!input.empty()) title = input;
    
    std::cout << "New Author: ";
    std::getline(std::cin, input);
    if (!input.empty()) author = input;
    
    std::cout << "New Price: $";
    std::getline(std::cin, input);
    if (!input.empty() && DataHandler::validateNumericInput(input)) {
        double newPrice = std::stod(input);
        if (DataHandler::validatePositiveNumber(newPrice)) {
            price = newPrice;
        } else {
            std::cout << "Invalid price. Keeping current value." << std::endl;
        }
    }
    
    std::cout << "New Quantity: ";
    std::getline(std::cin, input);
    if (!input.empty()) {
        try {
            int newQuantity = std::stoi(input);
            if (newQuantity >= 0) {
                quantity = newQuantity;
            } else {
                std::cout << "Invalid quantity. Keeping current value." << std::endl;
            }
        } catch (const std::exception&) {
            std::cout << "Invalid quantity. Keeping current value." << std::endl;
        }
    }
}

void Book::updateQuantity(int newQuantity) {
    if (newQuantity >= 0) {
        quantity = newQuantity;
    }
}

// Book management functions
std::vector<Book> loadBooks() {
    std::vector<Book> books;
    DataHandler::createFileIfNotExists("books.txt");
    
    std::ifstream file("books.txt");
    if (!file.is_open()) {
        DataHandler::displayFileError("books.txt", "open");
        return books;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::vector<std::string> data = DataHandler::split(line, '|');
        if (data.size() >= 5) {
            try {
                int id = std::stoi(data[0]);
                std::string title = data[1];
                std::string author = data[2];
                double price = std::stod(data[3]);
                int quantity = std::stoi(data[4]);
                
                books.emplace_back(id, title, author, price, quantity);
            } catch (const std::exception&) {
                std::cout << "Warning: Skipped invalid book record." << std::endl;
            }
        }
    }
    
    file.close();
    return books;
}

void saveBooks(const std::vector<Book>& books) {
    std::ofstream file("books.txt");
    if (!file.is_open()) {
        DataHandler::displayFileError("books.txt", "save");
        return;
    }
    
    for (const auto& book : books) {
        file << book.getId() << "|"
             << book.getTitle() << "|"
             << book.getAuthor() << "|"
             << std::fixed << std::setprecision(2) << book.getPrice() << "|"
             << book.getQuantity() << std::endl;
    }
    
    file.close();
}

Book* findBookById(std::vector<Book>& books, int id) {
    auto it = std::find_if(books.begin(), books.end(),
                          [id](const Book& book) { return book.getId() == id; });
    return (it != books.end()) ? &(*it) : nullptr;
}

int generateNewBookId() {
    std::vector<Book> books = loadBooks();
    int maxId = 0;
    for (const auto& book : books) {
        if (book.getId() > maxId) {
            maxId = book.getId();
        }
    }
    return maxId + 1;
}

void viewAllBooks() {
    std::vector<Book> books = loadBooks();
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << std::setw(45) << "AVAILABLE BOOKS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    if (books.empty()) {
        std::cout << "No books available in the inventory." << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        return;
    }
    
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(25) << "TITLE"
              << std::setw(20) << "AUTHOR"
              << std::setw(10) << "PRICE"
              << std::setw(8) << "QTY" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (const auto& book : books) {
        book.display();
    }
    
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "Total Books: " << books.size() << std::endl;
}

void addBook() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << std::setw(30) << "ADD NEW BOOK" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    std::string title, author, priceStr, quantityStr;
    
    std::cout << "Enter Book Title: ";
    std::cin.ignore();
    std::getline(std::cin, title);
    
    if (title.empty()) {
        std::cout << "Error: Book title cannot be empty!" << std::endl;
        return;
    }
    
    std::cout << "Enter Author Name: ";
    std::getline(std::cin, author);
    
    if (author.empty()) {
        std::cout << "Error: Author name cannot be empty!" << std::endl;
        return;
    }
    
    std::cout << "Enter Price: $";
    std::getline(std::cin, priceStr);
    
    if (!DataHandler::validateNumericInput(priceStr)) {
        std::cout << "Error: Invalid price format!" << std::endl;
        return;
    }
    
    double price = std::stod(priceStr);
    if (!DataHandler::validatePositiveNumber(price)) {
        std::cout << "Error: Price must be positive!" << std::endl;
        return;
    }
    
    std::cout << "Enter Quantity: ";
    std::getline(std::cin, quantityStr);
    
    int quantity;
    try {
        quantity = std::stoi(quantityStr);
        if (quantity < 0) {
            std::cout << "Error: Quantity cannot be negative!" << std::endl;
            return;
        }
    } catch (const std::exception&) {
        std::cout << "Error: Invalid quantity format!" << std::endl;
        return;
    }
    
    int newId = generateNewBookId();
    Book newBook(newId, title, author, price, quantity);
    
    std::vector<Book> books = loadBooks();
    books.push_back(newBook);
    saveBooks(books);
    
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "SUCCESS: Book added successfully!" << std::endl;
    std::cout << "Book ID: " << newId << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void updateBook() {
    std::vector<Book> books = loadBooks();
    
    if (books.empty()) {
        std::cout << "\nNo books available to update!" << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << std::setw(30) << "UPDATE BOOK" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    viewAllBooks();
    
    std::cout << "\nEnter Book ID to update: ";
    std::string idStr;
    std::cin >> idStr;
    
    int id;
    try {
        id = std::stoi(idStr);
    } catch (const std::exception&) {
        std::cout << "Error: Invalid Book ID!" << std::endl;
        return;
    }
    
    Book* book = findBookById(books, id);
    if (book == nullptr) {
        std::cout << "Error: Book with ID " << id << " not found!" << std::endl;
        return;
    }
    
    book->updateDetails();
    saveBooks(books);
    
    std::cout << "\n" << std::string(50, '-') << std::endl;
    std::cout << "SUCCESS: Book updated successfully!" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

void deleteBook() {
    std::vector<Book> books = loadBooks();
    
    if (books.empty()) {
        std::cout << "\nNo books available to delete!" << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << std::setw(30) << "DELETE BOOK" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    viewAllBooks();
    
    std::cout << "\nEnter Book ID to delete: ";
    std::string idStr;
    std::cin >> idStr;
    
    int id;
    try {
        id = std::stoi(idStr);
    } catch (const std::exception&) {
        std::cout << "Error: Invalid Book ID!" << std::endl;
        return;
    }
    
    auto it = std::find_if(books.begin(), books.end(),
                          [id](const Book& book) { return book.getId() == id; });
    
    if (it == books.end()) {
        std::cout << "Error: Book with ID " << id << " not found!" << std::endl;
        return;
    }
    
    std::cout << "\nAre you sure you want to delete this book? (y/n): ";
    char confirm;
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        std::string deletedTitle = it->getTitle();
        books.erase(it);
        saveBooks(books);
        
        std::cout << "\n" << std::string(50, '-') << std::endl;
        std::cout << "SUCCESS: Book '" << deletedTitle << "' deleted successfully!" << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    } else {
        std::cout << "Delete operation cancelled." << std::endl;
    }
}
