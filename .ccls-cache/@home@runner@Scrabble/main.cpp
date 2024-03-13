/* Fecha: 12 marzo 2024
   Autor: Kevin Garay, Felipe Garrido , Arley Bernal
   Materia: Estructura de Datos
   Proyecto: Sistema de apoyo para el juego Scrabble
   Profesor: Ing. John Corredor, PhD
*/
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <string>

using namespace std;

// Estructura de dato de tipo mapa para guardar la configuración de comandos
map<string, map<string, string>> ayuda = {
    {"Configuración del juego.",
     {{"inicializar diccionario.txt",
       "Inicializa el sistema a partir del archivo diccionario.txt"},
      {"iniciar_inverso diccionario.txt",
       "Inicializa el sistema a partir del archivo y almacena las palabras en sentido inverso"},
      {"puntaje palabra",
       "El comando permite conocer la puntuación que puede obtenerse con una palabra dada"},
      {"salir", "Termina la ejecución de la aplicación"}}
    }
};

/**** TAD´s ***/
/* El TAD letra es usado para almacenar la información de una letra y su puntuación */
struct Letra {
    char letra;
    int puntos;
};

/* El TAD palabra es usado para almacenar la información de una palabra y el total de puntos */
struct Palabra {
    string palabra;
    int puntos;
};

/* El TAD diccionario es usado para almacenar una lista de palabras y otra de palabras inversas */
struct Diccionario {
    list<Palabra> palabras;
    list<Palabra> palabras_inversas;

    public:
        bool palabras_is_empty(){
            if (palabras.empty()){
                return true;
            } else { return false; }
        }
        bool palabras_inversas_is_empty(){
            if (palabras_inversas.empty()){
                return true;
            } else { return false; }
        }
};

/* Cabezaras de funciónes a usar */
list<Letra> leerletras(string nombreArch);
void executeCommand(string command);
bool inicializarDiccionario(const string& archivo, Diccionario& diccionario, bool invetir);
list<Palabra>::iterator buscarEnDiccionario(list<Palabra> &listaDePalabras, const string &word);
string puntaje_palabra(string word, list<Letra> letras, Diccionario &diccionario);

// main del programa
int main(){
    string command;
    Diccionario diccionario;

    // leer letras, esto deberia estar en un ciclo por si no se puede leer.
    list<Letra> letras = leerletras("letras.txt");
    if (letras.empty()) {
        return 0;
    }
    // Información sobre el uso de la terminal
    cout << endl << "ayuda                      Lista de comandos disponibles" << endl;
    cout << "ayuda nombre_comando       Descripción del comando" << endl;

    while (true) {
        // Entrada de comandos 
        cout << " $  ";
        getline(cin, command);

        // Bloque de condicionales para cada comando
        if (command.substr(0, 5) == "ayuda") {
            executeCommand(command);
        }
        else if (command.substr(0, 11) == "inicializar") {
            if (!diccionario.palabras_is_empty()){
                cout << "El diccionario ya ha sido inicializado.\n" << endl;
            } else {
                inicializarDiccionario(command.substr(12), diccionario, false);
            }
        } else if (command.substr(0, 15) == "iniciar_inverso") {
            if (!diccionario.palabras_inversas_is_empty()){
                cout << "El diccionario inverso ya ha sido inicializado.\n" << endl;
            } else {
                inicializarDiccionario(command.substr(16), diccionario, true);
            }        
        } else if (command == "puntaje palabra") {
            if (diccionario.palabras_is_empty() || diccionario.palabras_inversas_is_empty()){
              cout << "El diccionario y diccionario inverso no han sido inicializados.\n" << endl;
            } else {
              cout << "\nFuncion de puntaje de palabra ingresada\n";
              cout << "Ingrese la palabra: ";
              string word;
              cin >> word;
              cin.ignore();
              cout << puntaje_palabra(word, letras, diccionario) << endl;
            }
        } else if (command == "salir") {
            exit(0);
        } else {
            cout << "Comando no reconocido" << endl;
        }
    }
}


/* Función encargada de leer un archivo txt que contiene las letras del ingles y sus respectivos puntajes */
list<Letra> leerletras(string nombreArch) {
    list<Letra> letras;
    Letra letra;
    string line;
    // Se abre el archivo de texto con el nombre dado
    ifstream myfile(nombreArch);
    if (myfile.is_open()) {
        // Se lee el archivo linea por linea
        while (getline(myfile, line)) {
            istringstream iss(line);
            // Se lee la letra y el puntaje de la linea
            iss >> letra.letra >> letra.puntos;
            // Se agrega la letra  a la lista de letras
            letras.push_back(letra);
        }
        myfile.close();
        return letras;
    }
    else {
        cout << endl << "El archivo letras.txt no ha sido leído, se requiere revisión de archivo.\n" << endl;
        // retorna un lista vacia en caso de no poder leer el archivo
        return letras;
    }
}

/* Función encargada de dar información sobre los comandos y sus funcionalidades */
void executeCommand(string command) {
    if (command == "ayuda") {
        cout << endl
             << "Estos son los comandos disponibles para JaveScrabble " << endl;
        for (const auto &section : ayuda) {
            cout << endl << section.first << "\n";

            for (const auto &command : section.second) {
                cout << "     " << left << setw(40) << command.first << command.second << endl;
            }
            cout << endl;
        }
    } else if (command.substr(0, 6) == "ayuda ") {
        string specificCommand = command.substr(6);
        bool encontrado = false;
        for (const auto &section : ayuda) {
            for (const auto &entrada : section.second) {
                if (entrada.first.compare(specificCommand) == 0) {
                    cout << "     " << left << setw(40) << entrada.first << entrada.second << endl;
                    encontrado = true;
                    break;
                }
            }
            if (!encontrado) {
                cout << "Comando no encontrado." << endl;
            }
            cout << endl;
        }
    } else {
        cout << "Comando no encontrado" << endl;
    }
}

/* Función encargada de inicializar el diccionario */
bool inicializarDiccionario(const string& nomArchivo, Diccionario& diccionario, bool invertir) {
    ifstream fin(nomArchivo);
    list<Palabra> listaPalabras;
    string palabra;

    if (!fin.is_open()) {
        cout << "El archivo " << nomArchivo << " no existe o no puede ser leído.\n" << endl;
        return true;
    }

    while (fin >> palabra) {
        if (all_of(palabra.begin(), palabra.end(), ::isalpha)) {
            Palabra p;
            if (invertir) {
                reverse(palabra.begin(), palabra.end());
                p.palabra = palabra;
                diccionario.palabras_inversas.push_back(p);
            }
            p.palabra = palabra;
            diccionario.palabras.push_back(p);
        }
    }
    fin.close();
    string str = (!invertir) ? "diccionario" : "diccionario inverso";
    cout << "El " << str << " se ha inicializado correctamente.\n" << endl;
    return true;
}

/* Busca la posicion de la palabra en la lista de palbras del diccionario, si no se encuentra retorna un apuntador al final de la lista */
list<Palabra>::iterator buscarEnDiccionario(list<Palabra> &listaDePalabras, const string &word) {
    for (auto it = listaDePalabras.begin(); it != listaDePalabras.end(); ++it) {
        if (it->palabra == word) {
            return it;
        }
    }
    return listaDePalabras.end();
}

/* Calcula el puntaje de una palabra dada segun el puntaje de sus letras */
string puntaje_palabra(string word, list<Letra> letras, Diccionario &diccionario) {
    int puntaje = 0;
    for (char &c : word) {
      c = tolower(c);
    }
    string word_inv = word;

    // Verificar que la palabra contenga solo letras
    if (!all_of(word.begin(), word.end(), ::isalpha))
        return "La palabra " + word + "  contiene símbolos inválidos.\n";

    reverse(word_inv.begin(), word_inv.end());

    // Verificar que la palabra esté en los diccionarios
    auto it = buscarEnDiccionario(diccionario.palabras, word);
    auto it2 = buscarEnDiccionario(diccionario.palabras_inversas, word_inv);

    // sino existe retorna error
    if (it == diccionario.palabras.end() && it2 == diccionario.palabras_inversas.end())
        return "\nLa palabra " + word + " no existe en el diccionario\n";
    else {
        // Si la palabra existe en el diccionario, se calcula su puntaje
        for (char caracter : word)
            for (const auto letra : letras)
                if (letra.letra == caracter)
                    puntaje += letra.puntos;
        // insertamos puntajes al diccionario
        it->puntos = puntaje;
        it2->puntos = puntaje;
    }

    return "La palabra " + word + " tiene un puntaje de: " + to_string(puntaje) + "\n";
}