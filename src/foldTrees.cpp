#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sys/stat.h>
#include <iostream>
#include <fstream>


void createFile(const std::string& location, const std::string& fileName, const std::string& fileContents, bool allowWrite, bool allowRead) {
    // Concatenate the location and file name to create the full path
    std::string filePath = location + "/" + fileName;

    // Create an ofstream object to handle file operations
    std::ofstream fileStream(filePath);

    // Check if the file is successfully opened
    if (fileStream.is_open()) {
        // Write contents to the file
        fileStream << fileContents;

        // Calculate file permissions based on the boolean parameters
        int permissions = 0;

        if (allowWrite && allowRead) {
            permissions = 0600;  // Read and write
        } else if (allowWrite) {
            permissions = 0200;  // Write only
        } else if (allowRead) {
            permissions = 0400;  // Read only
        } // If neither allowWrite nor allowRead, permissions remain 0 (no special permissions)

        // Set file permissions using the chmod command
        chmod(filePath.c_str(), permissions);

        // Close the file
        fileStream.close();

        std::cout << "File created successfully at: " << filePath << std::endl;
    } else {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
}


int checkFileExtension(const std::string& filename) {
    size_t dotPosition = filename.find_last_of('.');

    return (dotPosition != std::string::npos && filename.substr(dotPosition + 1) == "dit") ? 0 : 1;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Modo de uso: " << argv[0] << " <filename.dit>" << std::endl;
        return 1;
    } else {
        int isDit = checkFileExtension(argv[1]);
        if (isDit != 0) {
            std::cerr << "Debe ingresar un archivo con formato *.dit" << std::endl;
            return 1;
        }
    }
    createFile("Dependencias/carpetas", "example.txt", "Hello, this is the content of the file.", true, true);
    return 0;
}
