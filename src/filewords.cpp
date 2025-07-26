#include <iostream>   // Librería para entrada y salida estándar
#include <fstream>    // Librería para manejar archivos
#include <vector>     // Para usar vectores
#include <string>     // Para manipular cadenas de texto

using namespace std;

// Función que lee palabras desde un archivo según el nivel
vector<string> leerPalabrasPorNivel(int nivel) 
{
    // Construye el nombre del archivo basado en el nivel recibido
    string nombreArchivo = "datafile/nivel" + to_string(nivel) + ".txt";

    ifstream archivo(nombreArchivo); // Abre el archivo para lectura

    vector<string> palabras; // Vector que almacenará las palabras
    string linea;

    // Verifica si el archivo se pudo abrir correctamente
    if (archivo.is_open()) {
        // Lee cada línea del archivo
        while (getline(archivo, linea)) {
            // Ignora líneas vacías
            if (!linea.empty())
                palabras.push_back(linea); // Agrega la palabra al vector
        }
        archivo.close(); // Cierra el archivo al terminar
    } else {
        // Muestra mensaje de error si el archivo no se abre
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }

    return palabras; // Retorna el vector con las palabras encontradas
}
