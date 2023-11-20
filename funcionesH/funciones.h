#ifndef FUNCIONES_H
#define FUNCIONES_H

#include <vector>
#include <unordered_map>
#include <cstdlib>
#include <string>
#include <iostream>

// Declare the function here
int calculateSum(const std::vector<int>& vec);

double calculateMean(const std::vector<int>& vec);

int calculateMode(const std::vector<int>& vec);

int calculateVectorLength(const std::vector<int>& vec);

void cerrarPrograma();

bool executeWordCounter(const std::string& param1, const std::string& param2, const std::string& param3, const std::string& param4);

void executeInvertedIndex(const std::string& param1, const std::string& param2);

int executeGraph ();

#endif // FUNCIONES_H
