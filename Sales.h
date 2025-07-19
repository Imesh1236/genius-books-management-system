#ifndef SALES_H
#define SALES_H

#include <string>
#include <vector>

class Sale {
private:
    int saleId;
    int bookId;
    std::string bookTitle;
    int quantitySold;
    double totalAmount;
    std::string saleDate;

public:
    Sale();
    Sale(int id, int bId, const std::string &bTitle, int qty, double amount, const std::string &date);
    
    // Getters
    int getSaleId() const;
    int getBookId() const;
    std::string getBookTitle() const;
    int getQuantitySold() const;
    double getTotalAmount() const;
    std::string getSaleDate() const;
    
    // Setters
    void setSaleId(int id);
    void setBookId(int bId);
    void setBookTitle(const std::string &bTitle);
    void setQuantitySold(int qty);
    void setTotalAmount(double amount);
    void setSaleDate(const std::string &date);
    
    // Display method
    void display() const;
};

// Sales management functions
void recordNewSale();
void viewSalesHistory();
void viewSalesReport();
std::vector<Sale> loadSales();
void saveSales(const std::vector<Sale>& sales);
int generateNewSaleId();
std::string getCurrentDate();

#endif
