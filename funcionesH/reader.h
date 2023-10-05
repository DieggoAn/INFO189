#ifndef FILE_HELPERS_H
#define FILE_HELPERS_H

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <vector>
#include <regex>
#include <map>

void loadEnvFromFile(const std::string& envFilePath);

bool fileReader(const std::string& filename, const std::string& keyword);

std::string getAccessLevel(const std::string& filename, const std::string& keyword);

std::string getName(const std::string& filename, const std::string& keyword);

int deployMenu(const std::string& filename, const std::string& name, const std::string& accessLevel);

void createNewTxtFile(const std::string& filename); 

bool searchFileInNewFiles(const std::string& filename);

void appendToFile(const std::string& filename, const std::string& content);

std::string findPath(const std::string& filename, const std::string& keyword);

#endif // FILE_HELPERS_H
