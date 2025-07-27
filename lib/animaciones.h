#ifndef ANIMACIONES_H
#define ANIMACIONES_H

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <windows.h>  

using namespace std;

/**
 * @brief Muestra el menú principal con un título en arte ASCII y un mensaje parpadeante.
 * 
 * Esta función limpia la consola y presenta una animación de título,
 * seguida por un mensaje que invita al jugador a presionar ENTER, con
 * efecto de puntos que parpadean. Al final, espera a que el usuario presione ENTER.
 * 
 * @return void
 */
inline void animarMenu()
{
    system("cls");  

    string titulo = R"( 
     ___    _   _   ____   ____   ____   ___   ____   ___  
    / _ \  | | | | |  _ \ |  _ \ |  _ \ / _ \ |  _ \ / _ \ 
   | | | | | | | | | | | || | | || | | | | | || |_) | | | |
   | |_| | | |_| | | |_| || |_| || |_| | |_| ||  _ <| |_| |
    \___/   \___/  |____/ |____/ |____/ \___/ |_| \_\\___/ 
    )";

    
    for (char c : titulo)
    {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(2));
    }

    cout << endl << endl;

    
    for (int i = 0; i < 3; i++)
    {
        cout << "Presiona ENTER para comenzar";
        cout << string(i + 1, '.');
        cout << "\r";
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(500));
    }

    cout << "Presiona ENTER para comenzar..." << endl;

    cin.ignore();
    cin.get();
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
        string mensaje = "¡Bien hecho!";
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
    string animacion = "Cargando próxima partida";
    cout << animacion;

    for (int i = 0; i < 3; ++i)
    {
        cout << ".";
        cout.flush();
        Sleep(500);
    }
    cout << "\nListo, ¡vamos a jugar!\n";
    Sleep(500);
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
    cout << "Preparando el siguiente nivel";
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
    const string mensaje = "¡¡¡GANASTE!!!";
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
    const string mensaje = "¡¡¡PERDISTE!!!";
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
#endif 
