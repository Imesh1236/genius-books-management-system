#include "Company.h"
#include <iostream>
#include <iomanip>

const std::string Company::companyName = "GENIUS BOOKS";
const std::string Company::address = "123 Knowledge Street, Book City, BC 12345";
const std::string Company::phone = "+1 (555) 123-BOOK";
const std::string Company::email = "info@geniusbooks.com";
const std::string Company::website = "www.geniusbooks.com";
const std::string Company::establishedYear = "1995";
const std::string Company::description = "Your Premier Destination for Knowledge and Literature";

void Company::displayCompanyDetails() {
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << std::setw(40) << "COMPANY INFORMATION" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    std::cout << std::left << std::setw(20) << "Company Name:" << companyName << std::endl;
    std::cout << std::left << std::setw(20) << "Established:" << establishedYear << std::endl;
    std::cout << std::left << std::setw(20) << "Description:" << description << std::endl;
    
    std::cout << "\n" << std::string(60, '-') << std::endl;
    std::cout << std::setw(30) << "CONTACT INFORMATION" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    std::cout << std::left << std::setw(20) << "Address:" << address << std::endl;
    std::cout << std::left << std::setw(20) << "Phone:" << phone << std::endl;
    std::cout << std::left << std::setw(20) << "Email:" << email << std::endl;
    std::cout << std::left << std::setw(20) << "Website:" << website << std::endl;
    
    std::cout << "\n" << std::string(60, '-') << std::endl;
    std::cout << std::setw(35) << "MISSION STATEMENT" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "At GENIUS BOOKS, we believe in the power of knowledge" << std::endl;
    std::cout << "and literature to transform lives. Since " << establishedYear << ", we have" << std::endl;
    std::cout << "been serving our community with the finest collection" << std::endl;
    std::cout << "of books, exceptional customer service, and a passion" << std::endl;
    std::cout << "for promoting literacy and learning." << std::endl;
    
    std::cout << "\n" << std::string(60, '-') << std::endl;
    std::cout << std::setw(30) << "OUR SERVICES" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "• Wide selection of books across all genres" << std::endl;
    std::cout << "• Special orders and rare book sourcing" << std::endl;
    std::cout << "• Educational materials and textbooks" << std::endl;
    std::cout << "• Reading recommendations and book clubs" << std::endl;
    std::cout << "• Corporate and bulk sales" << std::endl;
    
    std::cout << std::string(60, '=') << std::endl;
}

void Company::displayWelcomeMessage() {
    std::cout << "\n" << std::string(60, '*') << std::endl;
    std::cout << std::setw(40) << "WELCOME TO" << std::endl;
    std::cout << std::setw(45) << companyName << std::endl;
    std::cout << std::setw(50) << "MANAGEMENT SYSTEM" << std::endl;
    std::cout << std::string(60, '*') << std::endl;
    std::cout << std::setw(45) << description << std::endl;
    std::cout << std::string(60, '*') << std::endl;
}

std::string Company::getCompanyName() {
    return companyName;
}
