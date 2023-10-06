#include "../funcionesH/reader.h"

void loadEnvFromFile(const std::string& envFilePath) {
    std::ifstream file(envFilePath);
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            // Check if the line contains an environment variable assignment
            size_t equalsPos = line.find('=');
            if (equalsPos != std::string::npos) {
                std::string varName = line.substr(0, equalsPos);
                std::string varValue = line.substr(equalsPos + 1);
                
                // Set the environment variable in the current process
                setenv(varName.c_str(), varValue.c_str(), 1);
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open .env file: " << envFilePath << std::endl;
    }
}

bool fileReader(const std::string& filename, const std::string& keyword) {
    // Open the file
    std::ifstream inputFile(filename);

    // Check if the file is open
    if (!inputFile.is_open()) {
        std::cerr << "Failed to open the file." << std::endl;
        return false;
    }
    std::string line;
     while (std::getline(inputFile, line, ',')) {
        std::istringstream ss(line);
        std::string name;

        // Split the line using dot as a delimiter
        if (std::getline(ss, name, '.')) {
            if (name == keyword) {
                inputFile.close();
                return true;
            }
        }
    }

    // Close the file
    inputFile.close();
    std::cout << "Cannot find name in database" << std::endl;
    return false;
    };
    
std::string getName(const std::string& filename, const std::string& keyword){
// Open the file
    std::ifstream inputFile(filename);
    std::string line;
    
     while (std::getline(inputFile, line, ',')) {
        std::istringstream ss(line);
        std::string name;

        // Split the line using dot as a delimiter
        if (std::getline(ss, name, '.')) {
            if (name == keyword) {
                inputFile.close();
                return keyword;
            }
            }
        }
        inputFile.close();
        std::cout << "No se pudo encontrar el nombree en la base de datos " << std::endl;
        return 0;


}

std::string getAccessLevel(const std::string& filename, const std::string& keyword){
    // Open the file
    std::ifstream inputFile(filename);
    std::string line;
    
     while (std::getline(inputFile, line, ',')) {
        std::istringstream ss(line);
        std::string name;
        std::string accessLevel;

        // Split the line using dot as a delimiter
        if (std::getline(ss, name, '.') && (ss >> accessLevel)) {
            if (name == keyword) {
                inputFile.close();
                return accessLevel;
            }
            }
        }
        inputFile.close();
        std::cout << "No se pudo encontrar el nombre en la base de datos " << std::endl;
        return "";

}

int deployMenu(const std::string& filename, const std::string& name, const std::string& accessLevel) {
    std::ifstream file(filename);
    
    if (file.is_open()) {
        std::string line;
        std::cout<<"| Usuario: "<<name<<" | Nivel de acceso: "<<accessLevel<<" |"<<std::endl;
        while (std::getline(file, line)) {
            bool dotFound = false; // Flag to track if a dot is found in the line
            for (char c : line) {
                if (c == '.') {
                    std::cout << c;  // Print the dot
                    dotFound = true; // Set the flag to true
                } else if (!dotFound) {
                    std::cout << c;  // Print characters before the dot
                }
            }
            std::cout << std::endl;  // Add a newline after processing the line
        }
        file.close();
    } else {
        std::cout << "Archivo no encontrado" << std::endl;
    }

    return 0;
}

void createNewTxtFile(const std::string& filename) {


    // Construct the full path to the new file
    std::string filePath = "newFiles/" + filename + ".txt";
    // Create and open the new file
    std::ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        // File created successfully
    } 
}

bool searchFileInNewFiles(const std::string& filename) {
    // Construct the full path to the file in the "newFiles" folder
    std::string filePath = "newFiles/" + filename + ".txt";

    // Check if the file exists
    if (std::filesystem::exists(filePath)) {
        return true;
    } else {
        return false;
    }
}

void appendToFile(const std::string& filename, const std::string& content) {
    std::ofstream outputFile;
    std::string fullPath =  "newFiles/" + filename + ".txt";
    outputFile.open(fullPath, std::ios::app); // Open the file in append mode

    if (outputFile.is_open()) {
        outputFile << content << std::endl;
        outputFile.close();
    }
}

std::string findPath(const std::string& filename, const std::string& keyword) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return "";  // Return an empty string to indicate an error
    }

    std::regex pattern(keyword + "\\s*=\\s*([^\\s]+)");
    std::smatch match;
    std::string line;

    while (std::getline(file, line)) {
        if (std::regex_search(line, match, pattern)) {
            if (match.size() == 2) {
                return match[1];
            }
        }
    }

    // Return an empty string if the keyword was not found in the file
    return "";
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

void countWordsAndSave(const std::string& fileName, const std::string& bookPath, const std::string& charactersToInclude) {
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
    std::ofstream outFile(fileName);
    if (!outFile.is_open()) {
        std::cerr << "No se pudo crear el archivo de cuenta palabras: " << fileName << std::endl;
        return;
    }

    // Write word counts to the output file in descending order
    for (const auto& pair : sortedWordCount) {
        outFile << pair.first << ": " << pair.second << std::endl;
    }

    outFile.close();

    std::cout << "Se guardo la cuenta en: " << fileName << std::endl;
}
