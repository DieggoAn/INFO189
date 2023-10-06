#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <filesystem>
#include <regex>
#include <map>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h> // Include for getpid()

std::vector<std::string> getFilesInFolder(std::string& PATH_FILES_IN, std::string& extension) {
    std::vector<std::string> fileNames;
    std::cout << PATH_FILES_IN << std::endl;
    try {
        // Iterate over the entries in the folder
        for (const auto& entry : std::filesystem::directory_iterator(PATH_FILES_IN)) {
            std::string fileName = entry.path().filename().string();
            std::string fileExtension = fileName.substr(fileName.length() - 3);
            if (entry.is_regular_file() && fileExtension == extension) {
                fileNames.push_back(fileName);
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing folder: " << e.what() << std::endl;
    }

    return fileNames;
}


bool shouldInclude(char c, const std::string& charactersToInclude) {
    // Check if the character is in the list of characters to include
    for (char includeChar : charactersToInclude) {
        if (c == includeChar) {
            return true; // Include the character
        }
    }

    return false;
}

void countWordsAndSave(const std::string& outputFolder, const std::string& bookPath,const std::string bookName, const std::string& charactersToInclude) {
    std::ifstream bookFile(bookPath);
    if (!bookFile.is_open()) {
        std::cerr << "No se pudo encontrar el archivo: " << bookPath << std::endl;
        return;
    }
    // Create a map to store word counts
    std::map<std::string, int> wordCount;

    std::string word;
    while (bookFile >> word) {
        // Remove punctuation and convert to lowercase
        std::string cleanedWord; // Create a new string to store the cleaned word
        bool shouldAddWord = true; // Flag to control whether to add the word to the map

        for (char c : word) {
            if (shouldInclude(c, charactersToInclude)) {
                c = std::tolower(c);
                cleanedWord += c; // Append valid characters to the cleaned word
            } else {
                shouldAddWord = false; // Set the flag to false if the character should be excluded
                break; 
            }
        }
        // Check if we should add the word to the map
        if (shouldAddWord) {
            wordCount[cleanedWord]++;
        }
    }

    bookFile.close();

    // Create a vector of pairs for sorting
    std::vector<std::pair<std::string, int>> sortedWordCount(wordCount.begin(), wordCount.end());

    // Sort the vector in descending order based on word counts
    std::sort(sortedWordCount.begin(), sortedWordCount.end(),
              [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
                  return a.second > b.second;
              });

    // Create and open the output file
    std::ofstream outFile(outputFolder+bookName);
    if (!outFile.is_open()) {
        std::cerr << "No se pudo crear el archivo de cuenta palabras: " << outputFolder+bookName << std::endl;
        return;
    }

    // Write word counts to the output file in descending order
    for (const auto& pair : sortedWordCount) {
        outFile << pair.first << ", " << pair.second << std::endl;
    }

    std::thread::id threadID = std::this_thread::get_id();
    outFile.close();
    pid_t pid = getpid();
    std::cout <<"Proceso pid = "<< pid << " Archivo " << outputFolder+bookName << "procesado por el thread ID:" << threadID << std::endl;
}

void countWordsAndSaveWrapper(const std::string& pathOut, const std::string& pathIn, const std::string& fileName, const std::string& charactersToInclude) {
    countWordsAndSave(pathOut, pathIn, fileName, charactersToInclude);
}


int main(int argc, char* argv[]) {

    std::string extension = argv[1];
    std::string pathIn = argv[2];
    std::string pathOut = argv[3];
    std::string maxThreads = argv[4];

    std::cout << extension << " " << pathIn << " " << pathOut << " " << maxThreads << std::endl;
    std::vector<std::string> files = getFilesInFolder(pathIn, extension);
    std::string charactersToInclude = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúüÁÉÍÓÚñ";

    if (!files.empty()) {

        std::vector<std::thread> threads;

        // Create a mutex and condition variable for thread synchronization
        std::mutex mtx;
        std::condition_variable cv;

        // Function to execute by each thread
        auto threadFunction = [&]() {
            while (true) {
                std::string fileName;

                {
                    // Lock the mutex to access the shared files vector
                    std::unique_lock<std::mutex> lock(mtx);

                    // Check if there are files remaining to process
                    if (files.empty()) {
                        return; // No more files to process, exit the thread
                    }

                    // Get a file to process
                    fileName = files.back();
                    files.pop_back();
                }

                // Process the file
                countWordsAndSaveWrapper(pathOut, pathIn + fileName, fileName, charactersToInclude);
            }
        };

        // Create and start the threads
        for (int i = 0; i < std::stoi(maxThreads); ++i) {
            threads.emplace_back(threadFunction);
        }

        // Wait for all threads to finish
        for (std::thread& thread : threads) {
            thread.join();
        }
    }

    return 0;
}