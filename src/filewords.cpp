
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

// Lee palabras desde un archivo según el nivel y las retorna en un vector
vector<string> leerPalabrasPorNivel(int nivel) 
{
    string nombreArchivo = "datafile/nivel" + to_string(nivel) + ".txt";
    ifstream archivo(nombreArchivo);
    vector<string> palabras;
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (!linea.empty())
                palabras.push_back(linea);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
    }
    return palabras;
}

// Ejemplo de uso
/*
int main() {
    int nivel = 1; // Cambia el nivel según lo que necesites
    vector<string> palabras = leerPalabrasPorNivel(nivel);
    for (const auto& palabra : palabras) {
        cout << palabra << endl;
    }
    return 0;
}
*/
