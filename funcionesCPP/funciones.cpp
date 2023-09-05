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