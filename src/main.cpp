#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include <ctime>
#include <string>
#include "../lib/animaciones.h"
#include "../lib/IHtoolbox.h"
#include "../lib/dibujo.h"
#include "filewords.cpp" // Para leerPalabrasPorNivel
#include "../lib/color.h" 

#pragma comment(lib, "Xinput9_1_0.lib")

using namespace std;

// Variables globales
char gOpcion = ' ';
vector<string> gListaPalabras;
string palabra = "";
string fallidas = "";
int vida = 0;
bool correcta;
bool completa;
int nivel = 1;
const string tecladoVirtual = "abcdefghijklmnopqrstuvwxyz";

// Prototipos de funciones
char seleccionarLetraJoystick();
void esperarBotonA(const string& mensaje);
void ihJugarPartida();
int seleccionarNivelJoystick();
void mostrarMenuPrincipal();

// Función para seleccionar letra con joystick
char seleccionarLetraJoystick() {
    int indice = 0;
    cout << "Usa el stick " << BLACK << BG_YELLOW << "izquierdo" << RESET 
         << " para moverte y boton " << BLACK << BG_GREEN << " A " << RESET << " para seleccionar." << endl;
    
    while (true) {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD dwResult = XInputGetState(0, &state);

        if (dwResult == ERROR_SUCCESS) {
            SHORT x = state.Gamepad.sThumbLX;
            
            // Movimiento a la derecha
            if (x > 16000 && indice < tecladoVirtual.size() - 1) {
                indice++;
                Sleep(200);
            }
            if (x < -16000 && indice > 0) {
                indice--;
                Sleep(200);
            }

            // Mostrar teclado virtual
            cout << "\r";
            for (int i = 0; i < tecladoVirtual.size(); ++i) {
                if (i == indice) cout << "[" << tecladoVirtual[i] << "]";
                else cout << " " << tecladoVirtual[i] << " ";
            }
            cout << "   ";

            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
                cout << endl << BLUE << "Letra seleccionada: " << RESET << tecladoVirtual[indice] << endl;
                Sleep(300);
                return tecladoVirtual[indice];
            }
            // Detecta botón B y regresa valor especial
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
                Sleep(300);
                return '\0';
            }
        } else {
            cout << "\nJoystick no conectado. Conectalo y reinicia el juego." << RESET << endl;
            Sleep(1000);
            exit(1);
        }
        Sleep(50);
    }
}

// Función para esperar el botón A del joystick
void esperarBotonA(const string& mensaje) {
    cout << mensaje << endl;
    while (true) {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD dwResult = XInputGetState(0, &state);
        if (dwResult == ERROR_SUCCESS) {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
                Sleep(300);
                break;
            }
        }
        Sleep(50);
    }
}

// Función para seleccionar nivel con joystick
int seleccionarNivelJoystick() {
    int nivelSeleccionado = 1;
    XINPUT_STATE state;
    DWORD dwResult;
    
    cout << "Selecciona el nivel usando el stick izquierdo y boton " 
         << BLACK << BG_GREEN << " A " << RESET << " para confirmar:" << endl;
    
    bool nivelElegido = false;
    while (!nivelElegido) {
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        dwResult = XInputGetState(0, &state);
        
        if (dwResult == ERROR_SUCCESS) {
            SHORT y = state.Gamepad.sThumbLY;
            
            if (y > 16000 && nivelSeleccionado > 1) {
                nivelSeleccionado--;
                Sleep(200);
            }
            if (y < -16000 && nivelSeleccionado < 3) {
                nivelSeleccionado++;
                Sleep(200);
            }
            
            cout << "\rNivel: ";
            for (int i = 1; i <= 3; ++i) {
                if (i == nivelSeleccionado) cout << "[" << i << "] ";
                else cout << i << " ";
            }
            cout << "   ";
            
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
                Sleep(300);
                nivelElegido = true;
            }
        }
        Sleep(50);
    }
    cout << endl;
    return nivelSeleccionado;
}

// Función principal del juego
void ihJugarPartida() {
    srand((int)time(NULL));
    
    auto palabrasConPistas = leerPalabrasConPistas(nivel);
    if (palabrasConPistas.empty()) {
        cout << BLACK << "No hay palabras cargadas para este nivel." << RESET << endl;
        esperarBotonA("Presiona " + string(BLACK) + BG_GREEN + " A " + RESET + " para continuar...");
        return;
    }

    int nroAleatorio = rand() % palabrasConPistas.size();
    string palabraOriginal = palabrasConPistas[nroAleatorio].first;
    string pista = palabrasConPistas[nroAleatorio].second;
    
    palabra = string(palabraOriginal.size(), '_');
    fallidas = "";


    while (vida > 0)
    {
    while (vida > 0) {
        ihLimpiarPantalla();
        cout << MAGENTA << "Bienvenido al juego del ahorcado!" << RESET << endl;
        cout << "Nivel: " << nivel << endl;
        ihDibujarAhorcado(vida);
        cout << YELLOW << "Pista: " << RESET << pista << endl;
        cout << RED << "Fallos: " << fallidas << RESET << endl;
        cout << GREEN << "Progreso: " << palabra << RESET << endl;
        
        gOpcion = seleccionarLetraJoystick();
        correcta = false;

        // Verificar letra seleccionada
        for(int i = 0; i < palabraOriginal.size(); i++) {
            if(tolower(palabraOriginal[i]) == tolower(gOpcion)) {
                palabra[i] = gOpcion;
                correcta = true;
            }
        }

        if (!correcta) {
            vida--;
            fallidas += gOpcion;
            animacionFeedbackLetra(false); // Feedback de letra incorrecta
        } else {
            animacionFeedbackLetra(true);  // Feedback de letra correcta
        }

        // Verificar si se completó la palabra
        completa = true;
        for (char c : palabra) {
            if(c == '_') {
                completa = false;
                break;
            }
        }

        if(completa) {
            ihLimpiarPantalla();
            animacionVictoria();
            cout << BLUE << BG_CYAN << "::: A H O R C A D O :::" << RESET << endl;
            cout << LGREEN << "Felicidades, has ganado!" << RESET << endl;
            cout << BLUE << "La palabra era: " << RESET << palabraOriginal << endl;
            animacionCargaEntrePartidas();
            esperarBotonA("Presiona " + string(BLACK) + BG_GREEN + " A " + RESET + " para volver al menu principal...");
            return;
        }
    }

    // Manejo de derrota
    ihLimpiarPantalla();
    animacionDerrota();
    cout << CYAN << BG_BLUE << "::: A H O R C A D O :::" << RESET << endl;
    cout << RED << "Perdiste" << RESET << endl;
    cout << BLUE << "La palabra era: " << RESET << palabraOriginal << endl;
    animacionCargaEntrePartidas();
    esperarBotonA("Presiona " + string(BLACK) + BG_GREEN + " A " + RESET + " para volver al menu principal...");
}

// Función principal
int main() {
    cout << CYAN << "Programa iniciado..." << endl;
    animacionCargaInicial();
    
    // Verificar joystick
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    if (XInputGetState(0, &state) != ERROR_SUCCESS) {
        cout << "No se detecto joystick. Conectalo y reinicia el juego." << endl;
        system("pause");
        return 1;
    }
    
    while(true) {
        vida = 6;
        ihLimpiarPantalla();
        cout << YELLOW << "Bienvenido al juego del ahorcado!" << endl;
        cout << MAGENTA << ":::: MENU PRINCIPAL ::::" << RESET << endl;
        
        // Selección de nivel con joystick
        nivel = seleccionarNivelJoystick();
        gListaPalabras = leerPalabrasPorNivel(nivel);
        
        cout << "Presiona boton " << BLACK << BG_GREEN << " A " << RESET 
             << " para jugar, boton " << BLACK << BG_RED << " B " << RESET << " para salir." << endl;
        
        bool seleccion = false;
        while (!seleccion) {
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            if (XInputGetState(0, &state) == ERROR_SUCCESS) {
                if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
                    animacionTransicionNivel();
                    ihJugarPartida();
                    seleccion = true;
                }
                if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
                    cout << MAGENTA << "Gracias por jugar!" << RESET << endl;
                    return 0;
                }
            } else {
                cout << "Joystick desconectado." << endl;
                return 1;
            }
            Sleep(100);
        }
    }
    return 0;
}