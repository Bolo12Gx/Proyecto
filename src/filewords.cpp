#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility> // Para std::pair

using namespace std;

// FUNCIÓN PRINCIPAL QUE DEBES AÑADIR
vector<pair<string, string>> leerPalabrasConPistas(int nivel) {
    string nombreArchivo = "datafile/nivel" + to_string(nivel) + ".txt";
    ifstream archivo(nombreArchivo);
    vector<pair<string, string>> palabrasPistas;
    string linea;

    if (archivo.is_open()) {
        while (getline(archivo, linea)) {
            if (!linea.empty()) {
                size_t separador = linea.find('|');
                
                // Validación robusta del formato
                if (separador != string::npos && separador < linea.length() - 1) {
                    palabrasPistas.emplace_back(
                        linea.substr(0, separador), // Palabra
                        linea.substr(separador + 1) // Pista
                    );
                } else {
                    // Caso de error: línea sin formato correcto
                    palabrasPistas.emplace_back(
                        linea, // Palabra
                        "Pista no disponible" // Valor por defecto
                    );
                    cout << "Advertencia: Formato incorrecto en línea: " << linea << endl;
                }
            }
        }
        archivo.close();
    } else {
        cout << "Error crítico: No se pudo abrir " << nombreArchivo << endl;
    }
    return palabrasPistas;
}

// Función original que probablemente ya tienes
vector<string> leerPalabrasPorNivel(int nivel) {
    auto palabrasPistas = leerPalabrasConPistas(nivel); // Reutiliza la nueva función
    vector<string> palabras;
    for (const auto& par : palabrasPistas) {
        palabras.push_back(par.first);
    }
    return palabras;
}