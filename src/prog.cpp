#include "../funcionesH/funciones.h"
#include "../funcionesH/reader.h"
#include "../funcionesH/casos.h"
#include <getopt.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cstring>
#include <stdexcept>

int main(int argc, char* argv[]) {

    int option;

    std::string name;
    std::vector<int> numbers;
    std::string fileName = "";
    std::string text = "";
    std::string book = "";
    std::string wordCounter = ""; // Specify characters to ignore

    loadEnvFromFile("Dependencias/.env");

    if (getenv("PATH_FILES_IN") != nullptr && getenv("PATH_FILES_OUT") != nullptr && std::strcmp(getenv("PATH_FILES_IN"), getenv("PATH_FILES_OUT")) == 0) {
        std::cout << "Error: PATH_FILES_IN es igual a PATH_FILES_OUT. Porfavor cambia el directorio de alguno de ellos. " << std::endl;
        return 1;
    } else if (getenv("AMOUNT_THREADS") != nullptr) {
        const char* amountThreadsEnv = getenv("AMOUNT_THREADS");

        try {
            int amountThreads = std::stoi(amountThreadsEnv); // Convert environment variable to integer

            if (amountThreads > 10) {
                std::cerr << "Error: AMOUNT_THREADS es mayor que 10." << std::endl;
                return 1;
            }else if(amountThreads < 1) {
                std::cerr << "Error: AMOUNT_THREADS es menor que 1" << std::endl;
                return 1;
            }
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: AMOUNT_THREADS is not a valid integer." << std::endl;
            return 1;
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: AMOUNT_THREADS is out of range for an integer." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Error: AMOUNT_THREADS environment variable not set." << std::endl;
        return 1;
    }

    //funcion getopt que parsea los datos ingresados
    while ((option = getopt(argc, argv, "n:v:f:t:i:o:")) != -1) {
        switch (option) {
            case 'n':
                name = optarg;
                //std::cout << filePath << std::endl;
                if (fileReader(getenv("DB_PATH"),name) == false){ 
                    return 1;
                }
                break;
            case 'v':
                {
                    std::istringstream iss(optarg);
                    std::string element;
                    while (std::getline(iss, element, ';')) {
                        int num;
                        if (std::istringstream(element) >> num) {
                            numbers.push_back(num);
                        } else {
                            std::cerr << "Invalid input: " << element << std::endl;
                            return 1;
                        }
                    }
                }
                break;
            case 'f':
                fileName = optarg;
                break;
            case 't':
                text = optarg;
                break;
            case 'i':
                book = optarg;
                break;
            case 'o':
                wordCounter = optarg;
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " -n name -v numbers -f filename -t text -i filepath -o wordCounterName" << std::endl;
                return 1;
        }
    }

    int userInput;

    while (true) {
        // Display the user interface
        deployMenu(getenv("MENU_PATH"),name,getAccessLevel(getenv("DB_PATH"),name));

        // Wait for input from the user
        std::cout << "Es coja: ";
        std::cin >> userInput;
        if (hasAccess(userInput,getAccessLevel(getenv("DB_PATH"),name),getenv("MENU_PATH"))){
            caseManager(userInput,name,numbers,fileName,text,book,wordCounter);
        }
        // Pause to display the result and wait for user acknowledgment
        std::cout << "Presione Enter para continuar...";

        std::cin.ignore();
        std::cin.get();
        system("clear");
    }
    return 0;

}
