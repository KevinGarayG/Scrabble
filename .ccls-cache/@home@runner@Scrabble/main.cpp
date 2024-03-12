/* Fecha: 12 mar 2024
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

// configuración de comandos
map<string, map<string, string>> ayuda = {
    {"Configuración del juego.",
     {{"inicializar diccionario.txt",
       "Este comando inicializa un diccionario de palabras"},
      {"iniciar_inverso diccionario.txt",
       "Este comando inicializa un diccionario de palabras inversas"},
      {"iniciar_puntaje palabra",
       "Este comando calcula el puntaje de una persona dada"},
      {"salir", "Termina la ejecución de la aplicación"}}}};

// TAD´s
// El TAD de letra sirve para almacenar la información de una letra
struct Letra {
  char letra;
  int puntos;
};

// El TAD de palabra sirve para almacenar la información de una palabra
struct Palabra {
  string pal;
  int puntos;
};

// El TAD de diccionario sirve para almacenar palabras
struct Diccionarios {
  list<Palabra> palabras;
  list<Palabra> palabras_inversas;
};

// cabezaras de funciónes
list<Letra> leerletras(string nombreArch);
void executeCommand(string command);
list<Palabra>::iterator buscarEnDiccionario(list<Palabra> &listaDePalabras,
                                            const string &word);
string puntaje_palabra(string word, list<Letra> letras,
                       Diccionarios &diccionario);
bool cargarDiccionario(const string &archivo, Diccionarios &diccionario);

// main del programa
int main() {
  string command, nameFile;
  Diccionarios diccionario;
  nameFile = "letras.txt";

  // leer letras
  list<Letra> letras = leerletras(nameFile);
  if (letras.empty()) {
    cout << "No se pudo leer el archivo de letras\n\n" << endl;
    return 0;
  }
  cout << "ayuda                      Lista de comandos disponibles" << endl;
  cout << "ayuda nombre_comando       Descripción del comando" << endl;

  while (true) {
    cout << " $  ";
    getline(cin, command);

    if (command.substr(0, 5) == "ayuda") {
      executeCommand(command);
    } else if (command == "inicializar diccionario.txt") {
      cargarDiccionario("diccionario.txt", diccionario);

      cout << "Funcion de inicialización de diccionario\n";
    } else if (command == "iniciar_inverso diccionario.txt") {
      // código para cualquier otro caso
      cout << "Funcion de iniciar_inverso\n";
    } else if (command == "iniciar_puntaje palabra") {
      cout << "\nFuncion de puntaje de palabra ingresada\n";
      cout << "Ingrese la palabra: ";
      string word;
      cin >> word;
      // llamar funcion puntaje palabra
      cout << puntaje_palabra(word, letras, diccionario);
    } else if (command == "salir") {
      exit(0);
    } else {
      cout << "Comando no reconocido" << endl;
    }
    command = "";
  }
}

// lee un archivo txt que contiene las letras de un idioma y sus respectivos
// puntajes
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
  } else {
    cout << "No se pudo leer el archivo";
    // retorna un lista vacia en caso de no poder leer el archivo
    return letras;
  }
}

//
void executeCommand(string command) {
  if (command == "ayuda") {
    cout << endl
         << "Estos son los comandos disponibles para JaveScrabble " << endl;
    for (const auto &section : ayuda) {
      cout << endl << section.first << "\n";

      for (const auto &command : section.second) {
        cout << "     " << left << setw(40) << command.first << command.second
             << endl;
      }
      cout << endl;
    }
  } else if (command.substr(0, 6) == "ayuda ") {
    string specificCommand = command.substr(6);
    bool encontrado = false;
    for (const auto &section : ayuda) {
      for (const auto &entrada : section.second) {
        if (entrada.first.compare(specificCommand) == 0) {
          cout << "     " << left << setw(40) << entrada.first << entrada.second
               << endl;
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

// Función Inicializar ddiccionario
bool cargarDiccionario(const string &archivo, Diccionarios &diccionario) {
  ifstream fin(archivo);

  if (!fin.is_open()) {
    cout << "Archivo no existe " << archivo
         << " no existe o no puede ser leído." << endl;
    return false;
  }

  string palabra;
  while (fin >> palabra) {
    if (all_of(palabra.begin(), palabra.end(), ::isalpha)) {
      Palabra p;
      p.pal = palabra;
      diccionario.palabras.push_back(p);
    }
  }
  fin.close();

  cout << "Se ha inicializado correctamente \n";
  return true;
}

// busca la posicion de la palabra en la lista de palbras del diccionario, si no
// se encuentra retorna un apuntador al final de la lista
list<Palabra>::iterator buscarEnDiccionario(list<Palabra> &listaDePalabras,
                                            const string &word) {
  for (auto it = listaDePalabras.begin(); it != listaDePalabras.end(); ++it) {
    if (it->pal == word) {
      return it;
    }
  }
  return listaDePalabras.end();
}

// calcula el puntaje de una palabra
string puntaje_palabra(string word, list<Letra> letras,
                       Diccionarios &diccionario) {
  int puntaje = 0;
  string word_inv = word;
  reverse(word_inv.begin(), word_inv.end());

  // Verificar que la palabra contenga solo letras
  if (!all_of(word.begin(), word.end(), ::isalpha))
    return "\nLa palabra " + word + " contiene símbolos inválidos\n";

  // Verificar que la palabra esté en los diccionarios
  auto it = buscarEnDiccionario(diccionario.palabras, word);
  auto it2 = buscarEnDiccionario(diccionario.palabras_inversas, word_inv);

  // sino existe retorna error
  if (it == diccionario.palabras.end() &&
      it2 == diccionario.palabras_inversas.end())
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

  return "\nLa palabra " + word +
         " tiene un puntaje de: " + to_string(puntaje) + "\n";
}