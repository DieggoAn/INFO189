#ifndef CASOS_H
#define CASOS_H

#include <iostream>
#include <vector>

void caseManager(int option, const std::string& name, const std::vector<int>& vec,const std::string& fileName,const std::string& text, const std::string& libro, const std::string& wordCounter);

bool hasAccess(int number, const std::string& accessLevel, const std::string& filename);

bool accessManager(int option, const std::string& accessLevel);

#endif //CASOS_H
