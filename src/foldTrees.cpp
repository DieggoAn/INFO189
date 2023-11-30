#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <../Dependencias/json.hpp>

using json = nlohmann::json;
namespace fs = std::filesystem;

void createFile(const std::string& location, const std::string& fileName, const std::string& fileContents, const std::vector<std::string>& permissions) {
    // Concatenate the location and file name to create the full path
    std::string filePath = location;

    // Create an ofstream object to handle file operations
    std::ofstream fileStream(filePath);

    // Check if the file is successfully opened
    if (fileStream.is_open()) {
        // Write contents to the file
        fileStream << fileContents;

        // Calculate file permissions based on the vector of strings
        int filePermissions = 0;

        for (const std::string& permission : permissions) {
            if (permission == "escritura") {
                filePermissions |= S_IRUSR;  // User read
            } else if (permission == "lectura") {
                filePermissions |= S_IWUSR;  // User write
            } // Add more conditions for other permissions if needed
        }

        // Set file permissions using the chmod command
        chmod(filePath.c_str(), filePermissions);

        // Close the file
        fileStream.close();

        std::cout << "File created successfully at: " << filePath << std::endl;
    } else {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
}

void createFolder(const std::string& folderPath) {
    try {
        if (!fs::exists(folderPath)) {
            fs::create_directory(folderPath);
            std::cout << "Folder created successfully: " << folderPath << std::endl;
        } else {
            std::cerr << "Folder already exists: " << folderPath << std::endl;
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error creating folder: " << e.what() << std::endl;
    }
}

int checkFileExtension(const std::string& filename) {
    size_t dotPosition = filename.find_last_of('.');

    return (dotPosition != std::string::npos && filename.substr(dotPosition + 1) == "dit") ? 0 : 1;
}

void createObjects(const json& objects, const std::string& baseDir) {
    for (const auto& obj : objects) {
        std::string name = obj["nombre"];
        std::string type = obj["tipo"];

        if (type == "directorio") {
            std::string dirPath = baseDir + name + "/";
            createFolder(dirPath);

            if (obj.find("objetos") != obj.end()) {
                createObjects(obj["objetos"], dirPath);
            }
        } else if (type == "archivo") {
            std::string filePath = baseDir + name;
            std::string content = obj["contenido"];
            std::vector<std::string> permissions = obj["permisos"];

            createFile(filePath, name, content, permissions);
        }
    }
}

int main(int argc, char* argv[]) {

    std::string treeFile;
    std::cout <<"Ingrese direccion de archivo .dit: ";
    std::cin >> treeFile;
    int isDit = checkFileExtension(treeFile);
    while (isDit != 0){
        std::cout <<"Ingrese direccion de archivo .dit: ";
        std::cin >> treeFile;
        isDit = checkFileExtension(treeFile);
    }
    std::ifstream file(treeFile);
    if (file.is_open()) {
        json data;
        file >> data;
        file.close();
        std::string baseDir = data["dirbase"];
        createObjects(data["objetos"], baseDir);
        std::cout << std::endl;
    } else {
        std::cerr << "Error opening structure.json" << std::endl;
    }

    return 0;

}
