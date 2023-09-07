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

bool fileReader(const std::string& filename, const std::string& keyword);

std::string getAccessLevel(const std::string& filename, const std::string& keyword);

std::string getName(const std::string& filename, const std::string& keyword);

int deployMenu(const std::string& filename, const std::string& name, const std::string& accessLevel);

bool createNewTxtFile(const std::string& filePath); 

bool searchFileInNewFiles(const std::string& filename);

void appendToFile(const std::string& filename, const std::string& content);

std::string findPath(const std::string& filename, const std::string& keyword);

bool shouldInclude(char c, const std::string& charactersToInclude, const std::string& charactersToExclude);

void countWordsAndSave(const std::string& fileName, const std::string& bookPath, const std::string& charactersToInclude,const std::string& charactersToExclude);
#endif // FILE_HELPERS_H
