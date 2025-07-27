#ifndef ANIMACIONES_H
#define ANIMACIONES_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>  // para Sleep()
#include "../lib/color.h"  

using namespace std;

// Animación del menú principal con título tipo ASCII y mensaje parpadeante
inline void animacionMenuPrincipal()
{
    system("cls");  // Limpia pantalla

    string titulo = R"( 
     ___    _   _   ____   ____   ____   ___   ____   ___  
    / _ \  | | | | |  _ \ |  _ \ |  _ \ / _ \ |  _ \ / _ \
   | | | | | | | | | | | || | | || | | | | | || |_) | | | |
   | |_| | | |_| | | |_| || |_| || |_| | |_| ||  _ <| |_| |
    \___/   \___/  |____/ |____/ |____/ \___/ |_| \_\\___/
    )";

    // Mostrar título letra por letra simulando escritura
    for (char c : titulo)
    {
        cout << MAGENTA << c << RESET << flush;
        this_thread::sleep_for(chrono::milliseconds(2));
    }

    cout << endl << endl;

    // Animación de "Presiona ENTER para comenzar..." con puntos que parpadean
    for (int i = 0; i < 3; i++)
    {
        cout <<  "Presiona " << BLACK << BG_ORANGE << "ENTER" << RESET << " para comenzar" << RESET;
        cout << string(i + 1, '.');
        cout << "\r";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout <<  "Presiona " << BLACK << BG_ORANGE << "ENTER" << RESET << " para comenzar" << RESET << endl;

    cin.ignore();
    cin.get();
}

// Animación feedback tras elegir letra correcta o incorrecta
inline void animacionFeedbackLetra(bool acierto)
{
    system("cls");  // Limpia pantalla antes de mostrar feedback

    if (acierto)
    {
        string mensaje = " Bien hecho!";
        for (char c : mensaje)
        {
            cout << LGREEN << c << RESET << flush;
            this_thread::sleep_for(chrono::milliseconds(80));
        }
    }
    else
    {
        string mensaje = "Incorrecto...";
        for (char c : mensaje)
        {
            cout << RED <<  c << RESET << flush;
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    this_thread::sleep_for(chrono::milliseconds(800));
}

// Animación de carga inicial con spinner y porcentaje
inline void animacionCargaInicial()
{
    string spinner = "|/-\\";
    int spinnerLength = spinner.length();

    cout  << WHITE << "Cargando juego, por favor espera...\n" << RESET;
    for (int i = 0; i <= 100; ++i)
    {
        cout << CYAN << "\r" << spinner[i % spinnerLength] << " " << i << "%" << RESET ;
        Sleep(50);
        cout.flush();
    }
    cout << GREEN << "\nListo para jugar!\n" << RESET;
    Sleep(500);
}

// Animación simple entre partidas mostrando puntos animados
inline void animacionCargaEntrePartidas()
{
    string animacion = "\nCargando proxima partida";
    cout << CYAN << animacion;

    for (int i = 0; i < 3; ++i)
    {
        cout << ".";
        cout.flush();
        Sleep(500);
    }
    cout << GREEN << "\nListo, vamos a jugar!\n";
    Sleep(500);
}

// Animación de transición de nivel con puntos animados
inline void animacionTransicionNivel()
{
    cout << CYAN << "Preparando el siguiente nivel" << RESET << endl;
    for (int i = 0; i < 6; ++i)
    {
        cout << ".";
        cout.flush();
        Sleep(400);
    }
    cout << endl;
}

// Animación de victoria: parpadeo de "  GANASTE!!!"
inline void animacionVictoria()
{
    const string mensaje = " GANASTE!!!";
    const int repeticiones = 6;

    for (int i = 0; i < repeticiones; ++i)
    {
        if (i % 2 == 0)
            cout << LGREEN <<"\r" << mensaje << "      ";
        else
            cout << "\r" << string(mensaje.size(), ' ') << "      ";

        cout.flush();
        Sleep(400);
    }
    cout << endl;
}

// Animación de derrota: parpadeo de "  PERDISTE!!!"
inline void animacionDerrota()
{
    const string mensaje = " PERDISTE!!!";
    const int repeticiones = 6;

    for (int i = 0; i < repeticiones; ++i)
    {
        if (i % 2 == 0)
            cout << RED << "\r" << mensaje << "      ";
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
inline void animacionAhorcadoSaltando()
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


#endif // ANIMACIONES_H
