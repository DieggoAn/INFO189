#include "../funcionesH/funciones.h"

int calculateSum(const std::vector<int>& vec) {
    int sum = 0;
    for (int element : vec) {
        sum += element;
    }
    return sum;
}

double calculateMean(const std::vector<int>& vec) {
    int sum = 0;
    for (int element : vec) {
        sum += element;
    }
    double mean = static_cast<double>(sum) / vec.size();
    return mean; 
}

int calculateMode(const std::vector<int>& vec) {
    std::unordered_map<int, int> frequencyMap;

    // Count the frequency of each element
    for (int element : vec) {
        frequencyMap[element]++;
    }

    int mode = -1;
    int maxFrequency = 0;

    // Find the element with the highest frequency (mode)
    for (const auto& entry : frequencyMap) {
        if (entry.second > maxFrequency) {
            maxFrequency = entry.second;
            mode = entry.first;
        }
    }

    return mode;
}

int calculateVectorLength(const std::vector<int>& vec) {
    return vec.size();
}

void cerrarPrograma(){
    exit(0);
}

bool executeWordCounter(const std::string& param1, const std::string& param2, const std::string& param3, const std::string& param4, const std::string& param5) {
    std::string command = param5 + " " + param1 + " " + param2 + " " + param3 + " " + param4;
    int exitCode = std::system(command.c_str());
    bool success = false;
    if (exitCode == 0) {
        std::cout << "Se termino la cuenta de palabras." << std::endl;
        success = true;
    } else if (exitCode == 1){
        std::cerr << "Faltan archivos para realizar al indice." << std::endl;
    }else{
        std::cerr <<" Error al contar las palabras"<< std::endl;
    }
    return success;
}

void executeInvertedIndex(const std::string& param1, const std::string& param2, const std::string& param3){
    std::string command = param3 + " " + param1 + " " + param2;
    std::cout << "aaaaaaaa"<<std::endl;
    int exitCode = std::system(command.c_str());
}

void executeLlamarBuscador(const std::string& param1,const std::string& param2,const std::string& param3){
    std::string command = param3 + " " + param1 + " " + param2;
    int exitCode = std::system(command.c_str());
}
