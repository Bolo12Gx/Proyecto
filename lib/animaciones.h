#ifndef ANIMACIONES_H
#define ANIMACIONES_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>  
#include "../lib/color.h"
using namespace std;

void limpiarPantalla() 
{
    system("cls");
}
/**
 * @brief Muestra el menú principal con un título en arte ASCII y un mensaje parpadeante.
 * 
 * Esta función limpia la consola y presenta una animación de título con las palabras HANGMAN que significan ahorcado en inglés.
 * 
 * @return void
 */
inline void animarMenu()
{
    system("cls");  

    string titulo = R"( 

     _    _          _   _  _____  __  __           _   _   _ 
    | |  | |   /\   | \ | |/ ____||  \/  |   /\    | \ | | | |
    | |__| |  /  \  |  \| || |  __| \  / |  /  \   |  \| | | |
    |  __  | / /\ \ | . ` || | |_ | |\/| | / /\ \  | . ` | | |
    | |  | |/ ____ \| |\  || |__| | |  | |/ ____ \ | |\  | |_|
    |_|  |_/_/    \_\_| \_|\_____ |_|  |_|_/    \_ \_| \_| (_)
        )";

    
    for (char c : titulo)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(2));
    }

    Sleep(1000);
}

/**
 * @brief Muestra una animación de retroalimentación tras seleccionar una letra.
 * 
 * Según el resultado, se imprime un mensaje de éxito o error con animación tipo máquina de escribir.
 * 
 * @param acierto Valor booleano que indica si la selección fue correcta (true) o incorrecta (false).
 * 
 * @return void
 */
inline void animarSeleccion(bool acierto)
{
    system("cls"); 

    if (acierto)
    {
        string mensaje = "Bien hecho!";
        for (char c : mensaje)
        {
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(80));
        }
    }
    else
    {
        string mensaje = "Incorrecto...";
        for (char c : mensaje)
        {
            cout << c << flush;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    this_thread::sleep_for(chrono::milliseconds(800));
}

/**
 * @brief Muestra una animación de carga inicial con un spinner giratorio y porcentaje.
 * 
 * Esta función imprime un spinner de carga (| / - \) junto con el porcentaje
 * desde 0% hasta 100%, simulando una barra de carga.
 * 
 * @return void
 */
inline void mostrarSpinner()
{
    string spinner = "|/-\\";
    int spinnerLength = spinner.length();

    cout << "Cargando juego, por favor espera...\n";
    for (int i = 0; i <= 100; ++i)
    {
        cout << "\r" << spinner[i % spinnerLength] << " " << i << "%";
        Sleep(50);
        cout.flush();
    }
    cout << "\nListo para jugar!\n";
    Sleep(500);
}

/**
 * @brief Muestra una animación simple al cargar una nueva partida.
 * 
 * Simula un proceso de carga mediante puntos que aparecen progresivamente en pantalla.
 * 
 * @return void
 */
inline void animarCargaEntrePartidas()
{
    string animacion = "\nCargando partida";
    cout << animacion;

    for (int i = 0; i < 3; ++i)
    {
        cout << ".";
        cout.flush();
        Sleep(1000);
    }
    cout << "\nListo, vamos a jugar!\n";
    Sleep(1000);
}

/**
 * @brief Muestra una animación al cambiar de nivel.
 * 
 * Simula una transición de nivel mostrando puntos que se imprimen uno por uno.
 * 
 * @return void
 */
inline void animarTransicionNivel()
{
    cout << "\nPreparando el siguiente nivel";
    for (int i = 0; i < 6; ++i)
    {
        cout << ".";
        cout.flush();
        Sleep(400);
    }
    cout << endl;
}

/**
 * @brief Muestra una animación de victoria con texto parpadeante.
 * 
 * El mensaje "¡¡¡GANASTE!!!" aparece y desaparece varias veces simulando un parpadeo.
 * 
 * @return void
 */
inline void mostrarVictoria()
{
    const string mensaje = "GANASTE!!!";
    const int repeticiones = 6;

    for (int i = 0; i < repeticiones; ++i)
    {
        if (i % 2 == 0)
            cout << "\r" << mensaje << "      ";
        else
            cout << "\r" << string(mensaje.size(), ' ') << "      ";

        cout.flush();
        Sleep(400);
    }
    cout << endl;
}

/**
 * @brief Muestra una animación de derrota con texto parpadeante.
 * 
 * El mensaje "¡¡¡PERDISTE!!!" aparece y desaparece en bucle simulando parpadeo.
 * 
 * @return void
 */
inline void mostrarDerrota()
{
    const string mensaje = "PERDISTE!!!";
    const int repeticiones = 6;

    for (int i = 0; i < repeticiones; ++i)
    {
        if (i % 2 == 0)
            cout << "\r" << mensaje << "      ";
        else
            cout << "\r" << string(mensaje.size(), ' ') << "      ";

        cout.flush();
        Sleep(400);
    }
    cout << endl;
}
/**
 * @brief Muestra una animación donde el ahorcado salta.
 *
 * Imprime en consola una secuencia de dibujos ASCII que simulan al ahorcado moviéndose,
 * alternando entre varios frames. Al final muestra un mensaje de celebración.
 * No recibe parámetros ni retorna valores.
 */
inline void mostrarAhorcadoSaltando()
{
    const string frames[] = {
        R"(
   +---+
   |   |
       O
      /|\
      / \
 =========
)",
        R"(
   +---+
   |   |
       
      \O/
      / \
 =========
)",
        R"(
   +---+
   |   |
       
      \O/
      / \
 =========
)",
        R"(
   +---+
   |   |
       O
      /|\
      / \
 =========
)"
    };

    for (int i = 0; i < 6; ++i)
    {
        system("cls");
        cout << LGREEN << frames[i % 4] << RESET << endl;
        cout << YELLOW << "Felicidades, has ganado" << RESET << endl;
        Sleep(400);
    }
    Sleep(600);
}

/**
 * @brief Muestra la pestaña de créditos con colores y formato especial.
 *
 * Imprime los nombres de los autores con colores personalizados.
 */
inline void mostrarCreditos()
{
    limpiarPantalla();
    cout << BG_WHITE<< MAGENTA << "\n\t\t==== C R E D I T O S ====\n" << RESET << endl;
    cout << YELLOW << "\t\tJorge Guala" << RESET << endl;
    cout << CYAN   << "\t\tSandy Cunachi" << RESET << endl;
    cout << MAGENTA<< "\t\tJustin Cusquillo" << RESET << endl;
    cout << GREEN  << "\t\tMartin Correa" << RESET << endl;
    cout << ORANGE << "\t\tPablo Orozco" << RESET << endl;
    cout << ROSE   << "\t\tIsmael Heredia" << RESET << endl;
    cout << BG_LBLUE << BLACK << "\n\t\tGracias por jugar!\n" << RESET << endl;
    Sleep(2000);
}

#endif 