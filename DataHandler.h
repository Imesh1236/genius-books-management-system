#ifndef DATAHANDLER_H
#define DATAHANDLER_H

#include <string>
#include <fstream>
#include <vector>

class DataHandler {
public:
    // File operations
    static bool openFile(const std::string &filename, std::fstream &file, std::ios_base::openmode mode);
    static bool fileExists(const std::string &filename);
    static void createFileIfNotExists(const std::string &filename);
    
    // String utility functions
    static std::vector<std::string> split(const std::string &str, char delimiter);
    static std::string trim(const std::string &str);
    
    // Error handling
    static void displayFileError(const std::string &filename, const std::string &operation);
    static bool validateNumericInput(const std::string &input);
    static bool validatePositiveNumber(double number);
    static bool validatePositiveInteger(int number);
};

#endif
