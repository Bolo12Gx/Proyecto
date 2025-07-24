// niveles/niveles.h
#ifndef NIVELES_H
#define NIVELES_H

#include <vector>
#include <string>
using namespace std;

// Estructura para representar niveles del juego
struct Nivel 
{
    string nombre;
    vector<string> palabras;
};

// Funciones
vector<Nivel> obtenerNiveles();  // Devuelve todos los niveles
string seleccionarPalabra(const vector<string>& lista);

#endif
