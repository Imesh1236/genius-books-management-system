#include "DataHandler.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cctype>

bool DataHandler::openFile(const std::string &filename, std::fstream &file, std::ios_base::openmode mode) {
    file.open(filename, mode);
    if (!file.is_open()) {
        displayFileError(filename, "open");
        return false;
    }
    return true;
}

bool DataHandler::fileExists(const std::string &filename) {
    std::ifstream file(filename);
    return file.good();
}

void DataHandler::createFileIfNotExists(const std::string &filename) {
    if (!fileExists(filename)) {
        std::ofstream file(filename);
        if (file.is_open()) {
            file.close();
            std::cout << "Created new file: " << filename << std::endl;
        } else {
            displayFileError(filename, "create");
        }
    }
}

std::vector<std::string> DataHandler::split(const std::string &str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    
    return tokens;
}

std::string DataHandler::trim(const std::string &str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos) return "";
    
    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
}

void DataHandler::displayFileError(const std::string &filename, const std::string &operation) {
    std::cout << "\n========================================" << std::endl;
    std::cout << "           FILE ERROR" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Error: Unable to " << operation << " file '" << filename << "'" << std::endl;
    std::cout << "Please check if the file exists and you have proper permissions." << std::endl;
    std::cout << "========================================\n" << std::endl;
}

bool DataHandler::validateNumericInput(const std::string &input) {
    if (input.empty()) return false;
    
    size_t start = 0;
    if (input[0] == '-' || input[0] == '+') start = 1;
    
    bool hasDecimal = false;
    for (size_t i = start; i < input.length(); i++) {
        if (input[i] == '.') {
            if (hasDecimal) return false;
            hasDecimal = true;
        } else if (!std::isdigit(input[i])) {
            return false;
        }
    }
    
    return start < input.length();
}

bool DataHandler::validatePositiveNumber(double number) {
    return number > 0;
}

bool DataHandler::validatePositiveInteger(int number) {
    return number > 0;
}
