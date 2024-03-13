**Sistema de Apoyo para el Juego Scrabble**

Este proyecto consiste en un Sistema de Apoyo para el Juego Scrabble implementado en C++. Proporciona una interfaz interactiva en la terminal para que los usuarios puedan jugar Scrabble y realizar diversas operaciones relacionadas con el juego.

### Funcionalidades Principales:
1. **Lectura de Archivos:**
   - El sistema lee dos archivos de texto: "letras.txt" y "diccionario.txt".
   - "letras.txt" contiene las letras del alfabeto inglés junto con sus respectivos puntajes.
   - "diccionario.txt" contiene las palabras válidas del idioma.

2. **Comandos del Usuario:**
   - Los usuarios interactúan con el sistema ingresando comandos a través de la terminal.
   - Los comandos disponibles son:
     - `ayuda`: Muestra una lista de todos los comandos disponibles y sus descripciones.
     - `ayuda nombre_comando`: Muestra la descripción detallada de un comando específico.
     - `inicializar diccionario.txt`: Inicializa el sistema utilizando el archivo "diccionario.txt".
     - `inicializar_inverso diccionario.txt`: Inicializa el sistema utilizando el archivo "diccionario.txt" en orden inverso.
     - `puntaje palabra`: Calcula el puntaje de una palabra ingresada por el usuario.
     - `salir`: Termina la ejecución del programa.

3. **Tipos Abstractos de Datos (TADs):**
   - Se utilizan TADs para representar las letras, palabras y el diccionario del juego.
   - Cada TAD tiene atributos y operaciones específicas para su manejo.

4. **Funciones Principales:**
   - `leerletras(string nombreArch)`: Lee el archivo "letras.txt" y devuelve una lista de letras con sus puntajes.
   - `executeCommand(string command)`: Maneja los comandos ingresados por el usuario y proporciona ayuda según sea necesario.
   - `inicializarDiccionario(const string& nomArchivo, Diccionario& diccionario, bool invertir)`: Inicializa el diccionario a partir de un archivo de texto.
   - `puntaje_palabra(string word, list<Letra> letras, Diccionario &diccionario)`: Calcula el puntaje de una palabra ingresada por el usuario.
   - `buscarEnDiccionario(list<Palabra> &listaDePalabras, const string &word)`: Busca una palabra en la lista de palabras del diccionario.

### Requisitos:
- Compilador de C++
- Acceso a la terminal

### Uso:
1. Compilar el programa utilizando el compilador de C++.
2. Ejecutar el programa en la terminal.
3. Seguir las instrucciones y utilizar los comandos para interactuar con el sistema.

### Colaboradores:
- Kevin Garay 
- Arley Bernal
- Felipe Garrido

