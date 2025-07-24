#include "../lib/niveles.h"
#include <cstdlib>
#include <ctime>
using namespace std;
// Definimos los niveles y palabras con dificultad creciente
vector<Nivel> obtenerNiveles() {
    vector<Nivel> niveles = {
        {"Nivel 1", {"pc", "caja", "fibron", "teclado"}},
        {"Nivel 2", {"monitor", "telefono", "collar", "manzana"}},
        {"Nivel 3", {"microfono", "televisor"}},
        {"Nivel 4", {"computadora", "impresora", "auriculares"}},
        {"Nivel 5", {"refrigeradora", "electrocardiograma"}}
    };
    return niveles;
}

// Devuelve una palabra aleatoria del nivel
string seleccionarPalabra(const std::vector<std::string>& lista) {
    srand((unsigned int)time(NULL));
    int index = rand() % lista.size();
    return lista[index];
}
