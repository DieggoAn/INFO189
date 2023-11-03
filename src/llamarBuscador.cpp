#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <unistd.h>
#include <cctype>
#include <unordered_map>

std::map<std::string, std::vector<std::string>> mapLinesFromFile(const std::string& indexFile) {
    std::map<std::string, std::vector<std::string>> lineMap;

    // Open the input file
    std::ifstream inFile(indexFile);
    if (!inFile) {
        std::cerr << "Error opening the input file." << std::endl;
        return lineMap;  // Return an empty map in case of an error
    }

    // Read and store each line in the map
    std::string line;
    while (std::getline(inFile, line)) {
        // Parse the line and separate it into word and data
        size_t pos = line.find(',');
        if (pos != std::string::npos) {
            std::string word = line.substr(0, pos);
            std::string data = line.substr(pos + 1);

            // Add the line to the map
            lineMap[word].push_back(data);
        }
    }

    // Close the input file
    inFile.close();

    return lineMap;
}

std::vector<std::string> searchWordsInMap(const std::map<std::string, std::vector<std::string>>& lineMap, const std::string& searchInput) {
    std::istringstream iss(searchInput);
    std::vector<std::string> searchWords;

    // Divide la entrada en palabras individuales
    std::string word;
    while (iss >> word) {
        auto it = lineMap.find(word);
        if (it != lineMap.end()) {
            const std::vector<std::string>& data = it->second;
            searchWords.insert(searchWords.end(), data.begin(), data.end());
        }
    }

    return searchWords;
}

int countWords(const std::string& input) {
    std::istringstream iss(input);
    std::vector<std::string> words;
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    return words.size();
}

int main(int argc, char* argv[]) {
    // Define a map to store each line from the input file
    std::string indexFile = argv[1];
    std::string TOPK = argv[2];
    char seguir = 's';
    while (seguir == 's' ){

            std::map<std::string, std::vector<std::string>> lineMap = mapLinesFromFile(indexFile);
            std::string userInput = "";
            pid_t pid = getpid();

            std::cout << "“BUSCADOR BASADO EN INDICE INVERTIDO” (" << pid<<")" <<std::endl;
            std::cout << "Los top K documentos serán =: "<< TOPK <<std::endl;
            std::cout << "Escriba texto a buscar: ";
            std::getline(std::cin, userInput);
            int numWords = countWords(userInput);

            std::cout << "Respuesta: ";
            std::vector<std::string> filteredResult = searchWordsInMap(lineMap, userInput); 
            // Imprime los resultados

            for (const std::string& item : filteredResult) {
                std::cout << item << std::endl;
            }

            std::cout << std::endl;
            std::cout<<std::endl;

            std::cout << "Desea seguir (S/N):" ;
            std::cin >> seguir;
            seguir = std::tolower(static_cast<unsigned char>(seguir));
        }
    return 0;
    }
