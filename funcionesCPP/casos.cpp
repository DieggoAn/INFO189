#include "../funcionesH/casos.h"
#include "../funcionesH/funciones.h"
#include "../funcionesH/reader.h"


bool canIndex = false;


void caseManager(int option, const std::string& name, const std::vector<int>& vec,const std::string& fileName,const std::string& text, const std::string& libro, const std::string& wordCounter){

    switch (option) {
        case 0:
            cerrarPrograma();
            break;
        case 1:
            std::cout <<"Sumatoria del vector: " << calculateSum(vec)<< std::endl;
            break;
        case 2:
            std::cout << "Promedio del vector: " <<calculateMean(vec) << std::endl;
            break;
        case 3:
            std::cout <<"Moda del vector: " << calculateMode(vec)<< std::endl;
            break;
        case 4:
            std::cout <<"Largo del vector: " << calculateVectorLength(vec)<< std::endl;
            break;
        case 5:
            if (searchFileInNewFiles(fileName) == false){
                if(fileName != ""){
                    createNewTxtFile(fileName);
                 std::cout << "Archivo creado con exito..." << std::endl;
                }else{
                    std::cout << "No se ha ingresado texto..." << std::endl;
                }
            }else{
                std::cout << "Archivo ya se encuentra en la carpeta..." << std::endl;
            }
            break;
        case 6:
            if (searchFileInNewFiles(fileName) == true){
                if(text != ""){
                    appendToFile(fileName,text);
                    std::cout << "Se ha agregado texto al archivo..." << std::endl;
                }else{
                    std::cout << "No se ha ingresado texto..." << std::endl;
                }
            }else{
                std::cout << "No se pudo encontrar el archivo..." << std::endl;
            }
            break;
        case 7:
            if (searchFileInNewFiles(fileName)==false){
                std::string charactersToInclude = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZáéíóúüÁÉÍÓÚñ";
                if (std::filesystem::exists(libro)){
                    std::cout << "Contando palabras... "<<std::endl;
                    countWordsAndSave(wordCounter,libro,charactersToInclude);
                    std::cout << "Cuenta terminada." <<std::endl;
                }
            }else{
                std::cout<< "El archivo ya existe..."<<std::endl;
                }
            break;
        case 8:
            canIndex = executeWordCounter(getenv("EXTENSION"), getenv("PATH_FILES_IN"), getenv("PATH_FILES_OUT"), getenv("AMOUNT_THREADS"));
            break;
        case 9:
            if (canIndex == 1){
                executeInvertedIndex(getenv("PATH_FILES_OUT"), getenv("INVERTED_INDEX_FILE"));
            }else{
                std::cout << "Error. No se han preparado los archivos para al indice" <<std::endl;
            }
            break;
        case 11:
            if (executeGraph()==0){
                break;
            }else{
                std::cout << "Error al graficar los puntos.";
                break;
            }
        // Add more cases for other numbers
        default:
            std::cout << "la opcion "<< option << " aun no ha sido implementada" << std::endl;
            break;
    }


}

bool hasAccess(int number, const std::string& accessLevel, const std::string& filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return false;  // Return false to indicate an error
    }

    std::string line;
    while (std::getline(file, line)) {
        // Check if the line starts with the specified number
        if (line.find(std::to_string(number)) == 0) {
            // Check if the name is present within the line
            if (line.find(accessLevel) != std::string::npos) {
                file.close();  // Close the file
                return true;   // Name found, return true
            }else{
                std::cout<<"No tiene permisos para usar esta funcion."<<std::endl;
                return false;
            }
        }
    }
    // Name not found within the specified number's line
    std::cout<<"Funcion no se encuentra implementada."<<std::endl;
    file.close();  // Close the file
    return false;  // Return false
}

bool accessManager(int option, const std::string& accessLevel){
    if (hasAccess(1,"hola","nada")){
        return true;
    }else{
        std::cout << "Acceso denegado por falta de permisos !" << std::endl;
        return false;
    }
}