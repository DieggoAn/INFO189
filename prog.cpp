#include "funcionesH/funciones.h"
#include "funcionesH/reader.h"
#include "funcionesH/casos.h"
#include <getopt.h>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

int main(int argc, char* argv[]) {

    int option;

    std::string name;
    std::vector<int> numbers;
    std::string fileName = "";
    std::string text = "";
    std::string book = "";
    std::string wordCounter = "";

    //funcion getopt que parsea los datos ingresados
    while ((option = getopt(argc, argv, "n:v:f:t:i:o:")) != -1) {
        switch (option) {
            case 'n':
                name = optarg;
                if (fileReader(findPath("Dependencias/paths.txt","DB_PATH"),name) == false){ 
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
        deployMenu(findPath("Dependencias/paths.txt","MENU_PATH"),name,getAccessLevel(findPath("Dependencias/paths.txt","DB_PATH"),name));

        // Wait for input from the user
        std::cout << "Es coja: ";
        std::cin >> userInput;
        if (hasAccess(userInput,getAccessLevel(findPath("Dependencias/paths.txt","DB_PATH"),name),findPath("Dependencias/paths.txt","MENU_PATH"))){
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
