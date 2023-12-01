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

struct Node {
    string folderName;
    Node* next;

    Node(const string& name) : folderName(name), next(nullptr) {}
};

// Circular Linked List class
class CircularList {
public:
    CircularList() : head(nullptr), tail(nullptr) {}

    // Function to insert a folder node at the end of the list
    void insertFolder(const string& folderName) {
        Node* newNode = new Node(folderName);

        if (!head) {
            head = newNode;
            tail = newNode;
            newNode->next = head; // Circular link
        } else {
            tail->next = newNode;
            tail = newNode;
            newNode->next = head; // Circular link
        }
    }

    // Function to display the folders in the circular list
    void displayFolders() {
        if (!head) {
            cout << "List is empty." << endl;
            return;
        }

        Node* current = head;

        do {
            cout << current->folderName << " ->" << endl;
            current = current->next;
        } while (current != head);

        cout << "(circular)" << endl;
    }

    // Function to delete a folder node by name
void deleteFolder(const string& folderName) {
    if (!head) {
        cout << "List is empty. Cannot delete." << endl;
        return;
    }

    Node* current = head;
    Node* previous = nullptr;

    // Find the node to delete
    while (current->folderName != folderName && current->next != head) {
        previous = current;
        current = current->next;
    }

    if (current->folderName == folderName) {
        if (current == head) {
            if (head->next == head) {
                delete head;
                head = nullptr;
                tail = nullptr;
            } else {
                head = current->next;
                tail->next = head; // Update circular link
                delete current;
            }
        } else {
            previous->next = current->next;
            if (current == tail) {
                tail = previous; // Update tail if deleting the last node
            }
            delete current;
        }

        cout << "Folder '" << folderName << "' deleted." << endl;
    } else {
        cout << "Folder '" << folderName << "' not found." << endl;
    }
}

    ~CircularList() {
    if (!head) {
        return; // List is already empty
    }

    Node* current = head;

    do {
        Node* temp = current;
        current = current->next;
        delete temp;
    } while (current != head);

    head = nullptr;
    tail = nullptr;
}

private:
    Node* head;
    Node* tail;
};

void createFile(const string& location, const string& fileName, const string& fileContents, const vector<string>& permissions) {
    // Concatenate the location and file name to create the full path
    string filePath = location;

    // Create an ofstream object to handle file operations
    ofstream fileStream(filePath);

    // Check if the file is successfully opened
    if (fileStream.is_open()) {
        // Write contents to the file
        fileStream << fileContents;

        // Calculate file permissions based on the vector of strings
        int filePermissions = 0;

        for (const string& permission : permissions) {
            if (permission == "escritura") {
                filePermissions |= S_IRUSR;  // User read
            } else if (permission == "lectura") {
                filePermissions |= S_IWUSR;  // User write
            } // Add more conditions for other permissions if needed
        }

        // Set file permissions using the chmod command
        chmod(filePath.c_str(), filePermissions);

        // Close the file
        fileStream.close();

        cout << "File created successfully at: " << filePath << endl;
    } else {
        cerr << "Error opening file: " << filePath << endl;
    }
}

void directoryMaker(string dbase, vector<string> directorios, map<string, vector<string>> estructura){
    if (mkdir(dbase.c_str(), 0777) == 0) {
        cout << "Base folder created successfully." << endl;
    } else {
        cerr << "Error: Base folder could not be made." << endl;
    }
    CircularList lista;
    for (const string& elemento : directorios) {
        string subcarpeta = dbase + "/" + elemento;
        if (mkdir(subcarpeta.c_str(), 0777) == 0) {
            cout << "Folder " << elemento << " created successfully." << endl;
            lista.insertFolder(elemento);
        } else {
            cerr << "Error: Folder " << elemento << " could not be made." << endl;
        }
    }
    for (const auto& par : estructura) {
        for (const auto& valor : par.second) {
            string valor2 = valor + ".txt";
            string rutaArchivo = dbase+"/"+par.first+"/"+valor2;
            createFile(rutaArchivo, valor2, "", {"lectura","escritura"});
        }
    }
    lista.displayFolders();
}

void loadDreFromFile(const string& dreFilePath) {
    ifstream file(dreFilePath);
    string line, dbase;
    vector<string> directorios;
    map<string, vector<string>> estructuraDirectorios;
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
            directoryMaker(dbase, directorios, estructuraDirectorios);
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
    //system("pause");
    return 0;
}