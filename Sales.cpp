#include "Sales.h"
#include "Book.h"
#include "DataHandler.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <ctime>
#include <algorithm>
#include <map>

// Sale class implementation
Sale::Sale() : saleId(0), bookId(0), bookTitle(""), quantitySold(0), totalAmount(0.0), saleDate("") {}

Sale::Sale(int id, int bId, const std::string &bTitle, int qty, double amount, const std::string &date)
    : saleId(id), bookId(bId), bookTitle(bTitle), quantitySold(qty), totalAmount(amount), saleDate(date) {}

// Getters
int Sale::getSaleId() const { return saleId; }
int Sale::getBookId() const { return bookId; }
std::string Sale::getBookTitle() const { return bookTitle; }
int Sale::getQuantitySold() const { return quantitySold; }
double Sale::getTotalAmount() const { return totalAmount; }
std::string Sale::getSaleDate() const { return saleDate; }

// Setters
void Sale::setSaleId(int id) { saleId = id; }
void Sale::setBookId(int bId) { bookId = bId; }
void Sale::setBookTitle(const std::string &bTitle) { bookTitle = bTitle; }
void Sale::setQuantitySold(int qty) { quantitySold = qty; }
void Sale::setTotalAmount(double amount) { totalAmount = amount; }
void Sale::setSaleDate(const std::string &date) { saleDate = date; }

void Sale::display() const {
    std::cout << std::left << std::setw(8) << saleId
              << std::setw(8) << bookId
              << std::setw(25) << bookTitle.substr(0, 24)
              << std::setw(8) << quantitySold
              << std::setw(12) << std::fixed << std::setprecision(2) << totalAmount
              << std::setw(12) << saleDate << std::endl;
}

// Sales management functions
std::vector<Sale> loadSales() {
    std::vector<Sale> sales;
    DataHandler::createFileIfNotExists("sales.txt");
    
    std::ifstream file("sales.txt");
    if (!file.is_open()) {
        DataHandler::displayFileError("sales.txt", "open");
        return sales;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::vector<std::string> data = DataHandler::split(line, '|');
        if (data.size() >= 6) {
            try {
                int saleId = std::stoi(data[0]);
                int bookId = std::stoi(data[1]);
                std::string bookTitle = data[2];
                int quantitySold = std::stoi(data[3]);
                double totalAmount = std::stod(data[4]);
                std::string saleDate = data[5];
                
                sales.emplace_back(saleId, bookId, bookTitle, quantitySold, totalAmount, saleDate);
            } catch (const std::exception&) {
                std::cout << "Warning: Skipped invalid sales record." << std::endl;
            }
        }
    }
    
    file.close();
    return sales;
}

void saveSales(const std::vector<Sale>& sales) {
    std::ofstream file("sales.txt");
    if (!file.is_open()) {
        DataHandler::displayFileError("sales.txt", "save");
        return;
    }
    
    for (const auto& sale : sales) {
        file << sale.getSaleId() << "|"
             << sale.getBookId() << "|"
             << sale.getBookTitle() << "|"
             << sale.getQuantitySold() << "|"
             << std::fixed << std::setprecision(2) << sale.getTotalAmount() << "|"
             << sale.getSaleDate() << std::endl;
    }
    
    file.close();
}

int generateNewSaleId() {
    std::vector<Sale> sales = loadSales();
    int maxId = 0;
    for (const auto& sale : sales) {
        if (sale.getSaleId() > maxId) {
            maxId = sale.getSaleId();
        }
    }
    return maxId + 1;
}

std::string getCurrentDate() {
    time_t now = time(0);
    char* dt = ctime(&now);
    std::string dateStr(dt);
    // Remove newline character
    if (!dateStr.empty() && dateStr.back() == '\n') {
        dateStr.pop_back();
    }
    return dateStr;
}

void recordNewSale() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << std::setw(35) << "RECORD NEW SALE" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Display available books
    std::vector<Book> books = loadBooks();
    if (books.empty()) {
        std::cout << "No books available for sale!" << std::endl;
        return;
    }
    
    std::cout << "\nAvailable Books:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << std::left << std::setw(5) << "ID"
              << std::setw(25) << "TITLE"
              << std::setw(15) << "PRICE"
              << std::setw(8) << "QTY" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    for (const auto& book : books) {
        if (book.getQuantity() > 0) {
            std::cout << std::left << std::setw(5) << book.getId()
                      << std::setw(25) << book.getTitle().substr(0, 24)
                      << std::setw(15) << std::fixed << std::setprecision(2) << book.getPrice()
                      << std::setw(8) << book.getQuantity() << std::endl;
        }
    }
    
    std::cout << "\nEnter Book ID to sell: ";
    std::string bookIdStr;
    std::cin >> bookIdStr;
    
    int bookId;
    try {
        bookId = std::stoi(bookIdStr);
    } catch (const std::exception&) {
        std::cout << "Error: Invalid Book ID!" << std::endl;
        return;
    }
    
    Book* book = findBookById(books, bookId);
    if (book == nullptr) {
        std::cout << "Error: Book with ID " << bookId << " not found!" << std::endl;
        return;
    }
    
    if (book->getQuantity() <= 0) {
        std::cout << "Error: Book is out of stock!" << std::endl;
        return;
    }
    
    std::cout << "Selected Book: " << book->getTitle() << std::endl;
    std::cout << "Available Quantity: " << book->getQuantity() << std::endl;
    std::cout << "Price per unit: $" << std::fixed << std::setprecision(2) << book->getPrice() << std::endl;
    
    std::cout << "\nEnter quantity to sell: ";
    std::string quantityStr;
    std::cin >> quantityStr;
    
    int quantityToSell;
    try {
        quantityToSell = std::stoi(quantityStr);
        if (quantityToSell <= 0) {
            std::cout << "Error: Quantity must be positive!" << std::endl;
            return;
        }
        if (quantityToSell > book->getQuantity()) {
            std::cout << "Error: Not enough stock available!" << std::endl;
            return;
        }
    } catch (const std::exception&) {
        std::cout << "Error: Invalid quantity!" << std::endl;
        return;
    }
    
    double totalAmount = book->getPrice() * quantityToSell;
    
    std::cout << "\n" << std::string(40, '-') << std::endl;
    std::cout << "SALE SUMMARY:" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    std::cout << "Book: " << book->getTitle() << std::endl;
    std::cout << "Quantity: " << quantityToSell << std::endl;
    std::cout << "Unit Price: $" << std::fixed << std::setprecision(2) << book->getPrice() << std::endl;
    std::cout << "Total Amount: $" << std::fixed << std::setprecision(2) << totalAmount << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    
    std::cout << "\nConfirm sale? (y/n): ";
    char confirm;
    std::cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        // Create new sale record
        int newSaleId = generateNewSaleId();
        std::string currentDate = getCurrentDate();
        Sale newSale(newSaleId, bookId, book->getTitle(), quantityToSell, totalAmount, currentDate);
        
        // Update book quantity
        book->updateQuantity(book->getQuantity() - quantityToSell);
        
        // Save updated books
        saveBooks(books);
        
        // Save new sale
        std::vector<Sale> sales = loadSales();
        sales.push_back(newSale);
        saveSales(sales);
        
        std::cout << "\n" << std::string(50, '=') << std::endl;
        std::cout << "SUCCESS: Sale recorded successfully!" << std::endl;
        std::cout << "Sale ID: " << newSaleId << std::endl;
        std::cout << "Date: " << currentDate << std::endl;
        std::cout << std::string(50, '=') << std::endl;
    } else {
        std::cout << "Sale cancelled." << std::endl;
    }
}

void viewSalesHistory() {
    std::vector<Sale> sales = loadSales();
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << std::setw(45) << "SALES HISTORY" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    if (sales.empty()) {
        std::cout << "No sales records found." << std::endl;
        std::cout << std::string(80, '=') << std::endl;
        return;
    }
    
    std::cout << std::left << std::setw(8) << "SALE ID"
              << std::setw(8) << "BOOK ID"
              << std::setw(25) << "BOOK TITLE"
              << std::setw(8) << "QTY"
              << std::setw(12) << "AMOUNT"
              << std::setw(12) << "DATE" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    double totalRevenue = 0.0;
    for (const auto& sale : sales) {
        sale.display();
        totalRevenue += sale.getTotalAmount();
    }
    
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "Total Sales: " << sales.size() << std::endl;
    std::cout << "Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
}

void viewSalesReport() {
    std::vector<Sale> sales = loadSales();
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << std::setw(35) << "SALES REPORT" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    if (sales.empty()) {
        std::cout << "No sales data available for report." << std::endl;
        return;
    }
    
    // Calculate statistics
    double totalRevenue = 0.0;
    int totalQuantitySold = 0;
    std::map<int, int> bookSalesCount;
    std::map<int, std::string> bookTitles;
    
    for (const auto& sale : sales) {
        totalRevenue += sale.getTotalAmount();
        totalQuantitySold += sale.getQuantitySold();
        bookSalesCount[sale.getBookId()] += sale.getQuantitySold();
        bookTitles[sale.getBookId()] = sale.getBookTitle();
    }
    
    std::cout << "SUMMARY STATISTICS:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Total Sales Transactions: " << sales.size() << std::endl;
    std::cout << "Total Books Sold: " << totalQuantitySold << std::endl;
    std::cout << "Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << std::endl;
    std::cout << "Average Sale Amount: $" << std::fixed << std::setprecision(2) 
              << (sales.empty() ? 0.0 : totalRevenue / sales.size()) << std::endl;
    
    std::cout << "\nTOP SELLING BOOKS:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    // Sort books by sales count
    std::vector<std::pair<int, int>> sortedBooks(bookSalesCount.begin(), bookSalesCount.end());
    std::sort(sortedBooks.begin(), sortedBooks.end(),
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second;
              });
    
    int rank = 1;
    for (const auto& bookSale : sortedBooks) {
        if (rank > 5) break; // Show top 5
        std::cout << rank << ". " << bookTitles[bookSale.first] 
                  << " (Sold: " << bookSale.second << " copies)" << std::endl;
        rank++;
    }
    
    std::cout << std::string(60, '=') << std::endl;
}
