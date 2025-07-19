#include "User.h"
#include "DataHandler.h"
#include <iostream>
#include <fstream>
#include <vector>

User::User() : username(""), password(""), isLoggedIn(false) {}

bool User::login(const std::string &inputUsername, const std::string &inputPassword) {
    // Create users.txt if it doesn't exist with default admin user
    if (!DataHandler::fileExists("users.txt")) {
        std::ofstream file("users.txt");
        if (file.is_open()) {
            file << "admin,admin123" << std::endl;
            file << "manager,manager123" << std::endl;
            file.close();
            std::cout << "Default users created. Use 'admin/admin123' or 'manager/manager123' to login." << std::endl;
        }
    }
    
    std::ifstream file("users.txt");
    if (!file.is_open()) {
        DataHandler::displayFileError("users.txt", "open");
        return false;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        
        std::vector<std::string> credentials = DataHandler::split(line, ',');
        if (credentials.size() >= 2) {
            if (credentials[0] == inputUsername && credentials[1] == inputPassword) {
                username = inputUsername;
                password = inputPassword;
                isLoggedIn = true;
                file.close();
                return true;
            }
        }
    }
    
    file.close();
    return false;
}

void User::logout() {
    username = "";
    password = "";
    isLoggedIn = false;
    std::cout << "\n========================================" << std::endl;
    std::cout << "         LOGOUT SUCCESSFUL" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Thank you for using GENIUS BOOKS Management System!" << std::endl;
    std::cout << "You have been logged out successfully." << std::endl;
    std::cout << "========================================\n" << std::endl;
}

bool User::isUserLoggedIn() const {
    return isLoggedIn;
}

std::string User::getUsername() const {
    return username;
}

bool User::loadUsers() {
    return DataHandler::fileExists("users.txt");
}
