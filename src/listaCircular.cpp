#include <cstdlib> 
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sys/stat.h>

using namespace std;

map<string, vector<string>> estructuraDirectorios;

void loadDreFromFile(const string& dreFilePath) { //funcion para cargar variables de entorno
    ifstream file(dreFilePath);
    string line, dbase;
    vector<string> directorios;
    bool correcto = true;
    bool flag1 = false, flag2 = false;

    if (file.is_open()) {
        while ((getline(file, line))&&(correcto)) {
            // Check if the line contains an environment variable assignment
            size_t equalsPos = line.find('=');
            if (equalsPos != string::npos) {
                string varName = line.substr(0, equalsPos);
                string varValue = line.substr(equalsPos + 1);
                if ((varName=="dirbase")&&(!flag1)){
                    dbase = varValue;
                    flag1 = true;
                }
                else{
                    if ((varName=="dirs")&&(flag1)){
                        int init = 0;
                        int end = 0;
                        string nu = "";
                        while((end = varValue.find(";", init), end >= 0)){
                            nu = varValue.substr(init, end - init);
                            directorios.push_back(nu);
                            init = end + 1;
                        }
                        nu = varValue.substr(init, end - init);
                        directorios.push_back(nu);
                        flag2 = true;
                    }
                    else{
                        if ((!flag2)||(varName=="dirs")||(varName=="dirbase"))
                            correcto = false;
                        else{
                            auto it = find(directorios.begin(), directorios.end(), varName);
                            if (it == directorios.end())
                                correcto = false;
                            else{
                                vector<string> archivos;
                                int init = 0;
                                int end = 0;
                                string nu = "";
                                while((end = varValue.find(";", init), end >= 0)){
                                    nu = varValue.substr(init, end - init);
                                    archivos.push_back(nu);
                                    init = end + 1;
                                }
                                nu = varValue.substr(init, end - init);
                                archivos.push_back(nu);
                                estructuraDirectorios[varName]=archivos;
                            }
                        }
                    }
                }
            }
        }
        file.close();
        if(correcto){
            cout << ".dre opened successfully." << endl;
            if (mkdir(dbase.c_str(), 0777) == 0) {
                cout << "Folder created successfully." << endl;
            }
            else {
                cerr << "Error: Folder could not be made." << endl;
            }
        }
        else
            cerr << ".dre file is in the wrong format." << endl;
    } else {
        cerr << "Unable to open .dre file: " << dreFilePath << endl;
    }
}

int checkFileExtension(const string& filename) {
    size_t dotPosition = filename.find_last_of('.');

    return (dotPosition != string::npos && filename.substr(dotPosition + 1) == "dre") ? 0 : 1;
}
int main(){

    string circularFile;
    cout <<"Ingrese direccion de archivo .dre: ";
    cin >> circularFile;
    int isDre = checkFileExtension(circularFile);
    while (isDre != 0){
        std::cout <<"Ingrese direccion de archivo .dire: ";
        std::cin >> circularFile;
        isDre = checkFileExtension(circularFile);
    }
    loadDreFromFile(circularFile);
    system("pause");
    return 0;
}