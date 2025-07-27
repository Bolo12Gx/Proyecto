#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility> // Para std::pair

using namespace std;

/**
 * @brief Lee palabras y sus pistas desde un archivo de texto según el nivel.
 *
 * Cada línea del archivo debe tener el formato: palabra|pista
 * Si la línea no contiene el separador '|', se asigna "Pista no disponible" como pista.
 * El archivo se busca en la ruta: datafile/nivel<N>.txt, donde <N> es el número de nivel.
 *
 * @param nivel Número de nivel para seleccionar el archivo correspondiente.
 * @return std::vector<std::pair<std::string, std::string>> 
 *         Vector de pares donde el primer elemento es la palabra y el segundo la pista.
 */
vector<pair<string, string>> leerPalabrasConPistas(int nivel) {
    string nombreArchivo = "datafile/nivel" + to_string(nivel) + ".txt";
    ifstream archivo(nombreArchivo);
    vector<pair<string, string>> palabrasPistas;
    string linea;

    // Verifica si el archivo se pudo abrir correctamente
    if (archivo.is_open()) {
        // Lee cada línea del archivo
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
        archivo.close(); // Cierra el archivo al terminar
    } else {
        cout << "Error crítico: No se pudo abrir " << nombreArchivo << endl;
    }
    return palabrasPistas;
}

/**
 * @brief Lee solo las palabras desde el archivo de texto según el nivel.
 *
 * Utiliza leerPalabrasConPistas para obtener todas las palabras y pistas,
 * pero retorna únicamente las palabras en un vector.
 *
 * @param nivel Número de nivel para seleccionar el archivo correspondiente.
 * @return std::vector<std::string>
 *         Vector de palabras extraídas del archivo.
 */
vector<string> leerPalabrasPorNivel(int nivel) {
    auto palabrasPistas = leerPalabrasConPistas(nivel); // Reutiliza la nueva función
    vector<string> palabras;
    for (const auto& par : palabrasPistas) {
        palabras.push_back(par.first);
    }
    return palabras;
}