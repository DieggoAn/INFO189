#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <filesystem>
#include <unistd.h>

std::vector<std::string> getFilesInFolder(std::string& PATH_FILES_OUT) {
    std::vector<std::string> fileNames;
    try {
        // Iterate over the entries in the folder
        for (const auto& entry : std::filesystem::directory_iterator(PATH_FILES_OUT)) {
            std::string fileName = entry.path().filename().string();
            std::string fileExtension = fileName.substr(fileName.length() - 3);
            if (entry.is_regular_file()) {
                fileNames.push_back(fileName);
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing folder: " << e.what() << std::endl;
    }

    return fileNames;
}

// Define a struct to hold information about word occurrences in a file
struct WordOccurrence {
    std::string fileName;
    int count;
};

// Function to consolidate word occurrences from pre-parsed files
void consolidateWordOccurrences(const std::vector<std::string>& fileNames, const std::string& outputPath, const std::string& PATH_FILES_OUT) {
    std::unordered_map<std::string, std::vector<WordOccurrence>> wordOccurrences; // Map to store word occurrences

    // Iterate over the pre-parsed files
    for (const std::string& fileName : fileNames) {
        std::ifstream inputFile(PATH_FILES_OUT + fileName);
        // Read word occurrences from the file
        std::string word;
        int count;
        while (inputFile >> word >> count) {
            wordOccurrences[word].push_back({fileName, count});
        }

        inputFile.close();
    }

    // Open the output file for writing
    std::ofstream outputFile(outputPath);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Failed to open the output file." << std::endl;
    return;
}
    pid_t pid = getpid();
    std::cout <<"El proceso pid: " << pid << " Palabras procesadas: " << wordOccurrences.size() << " En el archivo: " << outputPath << std::endl;

    // Iterate over the wordOccurrences map and write results to the output file
    for (const auto& entry : wordOccurrences) {
        const std::string& word = entry.first;
        const std::vector<WordOccurrence>& occurrences = entry.second;

        outputFile << word << "";
        for (const WordOccurrence& occurrence : occurrences) {
            outputFile << "(" << occurrence.fileName << "," << occurrence.count << ");";
        }
        outputFile << std::endl;
    }

    // Close the output file
    outputFile.close();
}

int main(int argc, char* argv[]) {
    
    std::string indexFile = argv[2];
    std::string pathOut = argv[1];
    std::vector<std::string> fileNames = getFilesInFolder(pathOut);

    consolidateWordOccurrences(fileNames,indexFile, pathOut);

    return 0;
}