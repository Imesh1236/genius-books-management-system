#ifndef COMPANY_H
#define COMPANY_H

#include <string>

class Company {
private:
    static const std::string companyName;
    static const std::string address;
    static const std::string phone;
    static const std::string email;
    static const std::string website;
    static const std::string establishedYear;
    static const std::string description;

public:
    static void displayCompanyDetails();
    static void displayWelcomeMessage();
    static std::string getCompanyName();
};

#endif
