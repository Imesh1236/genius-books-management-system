#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
#include "User.h"
#include "Book.h"
#include "Sales.h"
#include "Company.h"
#include "DataHandler.h"

// Function prototypes
void displayMainMenu();
void displayBookManagementMenu();
void displaySalesManagementMenu();
void handleBookManagement();
void handleSalesManagement();
void clearScreen();
void pauseScreen();
int getMenuChoice();
bool handleLogin();

int main() {
    clearScreen();
    Company::displayWelcomeMessage();
    
    User currentUser;
    
    // Login loop
    while (!currentUser.isUserLoggedIn()) {
        if (!handleLogin()) {
            std::cout << "\nExiting application..." << std::endl;
            return 0;
        }
        
        std::string username, password;
        std::cout << "\nEnter Username: ";
        std::cin >> username;
        std::cout << "Enter Password: ";
        std::cin >> password;
        
        if (currentUser.login(username, password)) {
            std::cout << "\n" << std::string(50, '=') << std::endl;
            std::cout << "LOGIN SUCCESSFUL!" << std::endl;
            std::cout << "Welcome, " << currentUser.getUsername() << "!" << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            pauseScreen();
        } else {
            std::cout << "\n" << std::string(50, '=') << std::endl;
            std::cout << "LOGIN FAILED!" << std::endl;
            std::cout << "Invalid username or password." << std::endl;
            std::cout << "Please try again." << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            pauseScreen();
        }
    }
    
    // Main application loop
    int choice;
    do {
        clearScreen();
        displayMainMenu();
        choice = getMenuChoice();
        
        switch (choice) {
            case 1:
                clearScreen();
                viewAllBooks();
                pauseScreen();
                break;
                
            case 2:
                handleBookManagement();
                break;
                
            case 3:
                handleSalesManagement();
                break;
                
            case 4:
                clearScreen();
                Company::displayCompanyDetails();
                pauseScreen();
                break;
                
            case 5:
                currentUser.logout();
                pauseScreen();
                // Return to login
                while (!currentUser.isUserLoggedIn()) {
                    if (!handleLogin()) {
                        std::cout << "\nExiting application..." << std::endl;
                        return 0;
                    }
                    
                    std::string username, password;
                    std::cout << "\nEnter Username: ";
                    std::cin >> username;
                    std::cout << "Enter Password: ";
                    std::cin >> password;
                    
                    if (currentUser.login(username, password)) {
                        std::cout << "\n" << std::string(50, '=') << std::endl;
                        std::cout << "LOGIN SUCCESSFUL!" << std::endl;
                        std::cout << "Welcome back, " << currentUser.getUsername() << "!" << std::endl;
                        std::cout << std::string(50, '=') << std::endl;
                        pauseScreen();
                    } else {
                        std::cout << "\n" << std::string(50, '=') << std::endl;
                        std::cout << "LOGIN FAILED!" << std::endl;
                        std::cout << "Invalid username or password." << std::endl;
                        std::cout << "Please try again." << std::endl;
                        std::cout << std::string(50, '=') << std::endl;
                        pauseScreen();
                    }
                }
                break;
                
            case 6:
                std::cout << "\n" << std::string(60, '=') << std::endl;
                std::cout << std::setw(35) << "THANK YOU!" << std::endl;
                std::cout << std::string(60, '=') << std::endl;
                std::cout << "Thank you for using GENIUS BOOKS Management System!" << std::endl;
                std::cout << "Have a great day!" << std::endl;
                std::cout << std::string(60, '=') << std::endl;
                break;
                
            default:
                std::cout << "\nInvalid choice! Please select a valid option (1-6)." << std::endl;
                pauseScreen();
                break;
        }
        
    } while (choice != 6);
    
    return 0;
}

void displayMainMenu() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << std::setw(40) << "GENIUS BOOKS MANAGEMENT SYSTEM" << std::endl;
    std::cout << std::setw(35) << "MAIN MENU" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "1. View Available Book Details" << std::endl;
    std::cout << "2. Add/Update/Delete Book Details" << std::endl;
    std::cout << "3. Manage Sales Details" << std::endl;
    std::cout << "4. View Company Details" << std::endl;
    std::cout << "5. Logout" << std::endl;
    std::cout << "6. Exit" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    std::cout << "Enter your choice (1-6): ";
}

void displayBookManagementMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << std::setw(30) << "BOOK MANAGEMENT" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. View All Books" << std::endl;
    std::cout << "2. Add New Book" << std::endl;
    std::cout << "3. Update Book Details" << std::endl;
    std::cout << "4. Delete Book" << std::endl;
    std::cout << "5. Back to Main Menu" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Enter your choice (1-5): ";
}

void displaySalesManagementMenu() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << std::setw(30) << "SALES MANAGEMENT" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "1. Record New Sale" << std::endl;
    std::cout << "2. View Sales History" << std::endl;
    std::cout << "3. View Sales Report" << std::endl;
    std::cout << "4. Back to Main Menu" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Enter your choice (1-4): ";
}

void handleBookManagement() {
    int choice;
    do {
        clearScreen();
        displayBookManagementMenu();
        choice = getMenuChoice();
        
        switch (choice) {
            case 1:
                clearScreen();
                viewAllBooks();
                pauseScreen();
                break;
                
            case 2:
                clearScreen();
                addBook();
                pauseScreen();
                break;
                
            case 3:
                clearScreen();
                updateBook();
                pauseScreen();
                break;
                
            case 4:
                clearScreen();
                deleteBook();
                pauseScreen();
                break;
                
            case 5:
                return; // Back to main menu
                
            default:
                std::cout << "\nInvalid choice! Please select a valid option (1-5)." << std::endl;
                pauseScreen();
                break;
        }
        
    } while (choice != 5);
}

void handleSalesManagement() {
    int choice;
    do {
        clearScreen();
        displaySalesManagementMenu();
        choice = getMenuChoice();
        
        switch (choice) {
            case 1:
                clearScreen();
                recordNewSale();
                pauseScreen();
                break;
                
            case 2:
                clearScreen();
                viewSalesHistory();
                pauseScreen();
                break;
                
            case 3:
                clearScreen();
                viewSalesReport();
                pauseScreen();
                break;
                
            case 4:
                return; // Back to main menu
                
            default:
                std::cout << "\nInvalid choice! Please select a valid option (1-4)." << std::endl;
                pauseScreen();
                break;
        }
        
    } while (choice != 4);
}

void clearScreen() {
    // Clear screen for different operating systems
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

int getMenuChoice() {
    int choice;
    std::string input;
    
    std::getline(std::cin, input);
    if (input.empty()) {
        std::getline(std::cin, input);
    }
    
    try {
        choice = std::stoi(input);
    } catch (const std::exception&) {
        choice = -1; // Invalid choice
    }
    
    return choice;
}

bool handleLogin() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << std::setw(30) << "USER LOGIN" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Please login to continue." << std::endl;
    std::cout << "Default credentials:" << std::endl;
    std::cout << "Username: admin, Password: admin123" << std::endl;
    std::cout << "Username: manager, Password: manager123" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    std::cout << "Press 'q' to quit or any other key to continue: ";
    
    std::string input;
    std::cin >> input;
    
    if (input == "q" || input == "Q") {
        return false;
    }
    
    return true;
}
