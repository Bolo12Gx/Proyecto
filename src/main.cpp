#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include <ctime>
#include <string>
#include "../lib/IHtoolbox.h"
#include "../lib/dibujo.h"
#include "../lib/niveles.h"
#include "../src/niveles.cpp"
#pragma comment(lib, "Xinput9_1_0.lib")

using namespace std;

char gOpcion = 'a';

string palabra = "";
string fallidas = "";
int vida = 0;
bool correcta;
bool completa;

// Letras disponibles
const string tecladoVirtual = "abcdefghijklmnopqrstuvwxyz";

// Solo joystick
char seleccionarLetraJoystick() 
{
    XINPUT_STATE state;
    DWORD dwResult;

    int indice = 0;
    cout << "Usa el stick izquierdo para moverte y botón A para seleccionar." << endl;

    while (true) 
    {
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        dwResult = XInputGetState(0, &state);

        if (dwResult == ERROR_SUCCESS) 
        {
            SHORT x = state.Gamepad.sThumbLX;
            if (x > 16000 && indice < tecladoVirtual.size() - 1) 
            {
                indice++;
                Sleep(200);
            }
            {
                indice--;
                Sleep(200);
            }

            cout << "\r";
            for (int i = 0; i < tecladoVirtual.size(); ++i) 
            {
                if (i == indice) cout << "[" << tecladoVirtual[i] << "]";
                else cout << " " << tecladoVirtual[i] << " ";
            }
            cout << "   ";

            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) 
            {
                cout << endl << "Letra seleccionada: " << tecladoVirtual[indice] << endl;
                Sleep(300);
                return tecladoVirtual[indice];
            }
        } 
        else 
        {
            cout << "\nJoystick desconectado durante la partida." << endl;
            exit(1);
        }

        Sleep(50);
    }
}

void ihJugarPartida()
{
    std::vector<Nivel> niveles = obtenerNiveles();
    int nivelActual = 0;

    while (nivelActual < niveles.size()) 
    {
        vida = 6;
        palabra = "";
        fallidas = "";
        correcta = false;
        completa = false;

        std::string palabraOriginal = seleccionarPalabra(niveles[nivelActual].palabras);

        for (char c : palabraOriginal) 
        {
            palabra += "_";
        }

        while (vida > 0) 
        {
            ihLimpiarPantalla();
            cout << "::: " << niveles[nivelActual].nombre << " :::" << endl;
            ihDibujarAhorcado(vida);
            cout << "Fallos: " << fallidas << endl;
            cout << "Progreso: " << palabra << endl;
            cout << "Selecciona una letra con el joystick:" << endl;

            gOpcion = seleccionarLetraJoystick();
            correcta = false;

            for (int i = 0; i < palabraOriginal.size(); i++) 
            {
                if (palabraOriginal[i] == gOpcion) 
                {
                    palabra[i] = gOpcion;
                    correcta = true;
                }
            }

            if (!correcta)
            {
                vida--;
                fallidas += gOpcion;
            }

            completa = true;
            for (char c : palabra) 
            {
                if (c == '_') 
                {
                    completa = false;
                    break;
                }
            }

            if (completa) 
            {
                ihLimpiarPantalla();
                cout << "Has superado " << niveles[nivelActual].nombre << "!" << endl;
                nivelActual++;
                if (nivelActual < niveles.size()) 
                {
                    cout << "Avanzando al siguiente nivel..." << endl;
                    Sleep(2000);
                }
                break;
            }
        }

        if (vida == 0) 
        {
            ihLimpiarPantalla();
            cout << "Perdiste en " << niveles[nivelActual].nombre << endl;
            cout << "La palabra era: " << palabraOriginal << endl;
            cout << "Presiona botón A para volver al menú..." << endl;

            // Esperar botón A para volver
            XINPUT_STATE state;
            while (true) {
                ZeroMemory(&state, sizeof(XINPUT_STATE));
                if (XInputGetState(0, &state) == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) 
                {
                    break;
                }
                Sleep(100);
            }
            return;
        }
    }

    if (nivelActual == niveles.size()) 
    {
        ihLimpiarPantalla();
        cout << "¡¡¡FELICIDADES, completaste todos los niveles del ahorcado!!!" << endl;
        cout << "Presiona botón A para volver al menú..." << endl;

        XINPUT_STATE state;
        while (true) 
        {
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            if (XInputGetState(0, &state) == ERROR_SUCCESS && (state.Gamepad.wButtons & XINPUT_GAMEPAD_A)) 
            {
                break;
            }
            Sleep(100);
        }
    }
}

int main()
{
    cout << "Programa iniciado..." << endl;

    while (true)
    {
        vida = 6;
        ihLimpiarPantalla();
        cout << "Bienvenido al juego del ahorcado!" << endl;
        cout << ":::: MENU PRINCIPAL ::::" << endl;
        cout << "Presiona boton A para jugar, boton B para salir." << endl;

        bool seleccion = false;
        XINPUT_STATE state;

        while (!seleccion) {
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            DWORD dwResult = XInputGetState(0, &state);

            if (dwResult == ERROR_SUCCESS) {
                if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
                    ihJugarPartida();
                    seleccion = true;
                } else if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
                    cout << "Gracias por jugar!" << endl;
                    return 0;
                }
            } else {
                cout << "Joystick desconectado. Conectalo y reinicia el juego." << endl;
                return 1;
            }

            Sleep(100);
        }
    }

    return 0;
}

