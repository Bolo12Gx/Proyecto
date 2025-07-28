#include <iostream>     // Para imprimir en consola
#include "../lib/color.h" // Biblioteca personalizada para colores (se asume que define RESET)
#include <ctime>        // No se usa aquí, pero probablemente se usa en otro archivo

using namespace std;

/**
 * @brief Dibuja el estado actual del ahorcado en función de las vidas restantes.
 * 
 * @param vida Número de vidas restantes (de 6 a 0). Cada valor representa una etapa del dibujo.
 * 
 * El dibujo se va completando progresivamente:
 * - 6 vidas: estructura vacía
 * - 5 vidas: cabeza
 * - 4 vidas: torso
 * - 3 vidas: un brazo
 * - 2 vidas: ambos brazos
 * - 1 vida : una pierna
 * - 0 vidas: figura completa (ahorcado)
 */
void dibujarAhorcado(int vida)
{
    switch(vida)
    {
        case 6:
            // Estructura inicial sin figura
            cout << "  +---+\n"
                    "  |   |\n"
                    "      |\n"
                    "      |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n" << RESET;
            break;

        case 5:
            // Se dibuja la cabeza
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    "      |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n";
            break;

        case 4:
            // Se añade el torso
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    "  |   |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n";
            break;

        case 3:
            // Se añade un brazo
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    " /|   |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n";
            break;

        case 2:
            // Se añaden ambos brazos
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    " /|\\  |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n";
            break;

        case 1:
            // Se añade una pierna
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    " /|\\  |\n"
                    " /    |\n"
                    "      |\n"
                    "=========\n";
            break;

        case 0:
            // Figura completa (ahorcado)
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    " /|\\  |\n"
                    " / \\  |\n"
                    "      |\n"
                    "=========\n";
            break;
    }
}