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


//c++ src/main.cpp -o output/main.exe -lXinput9_1_0

#pragma comment(lib, "Xinput9_1_0.lib")

using namespace std;

char gOpcion = ' ';

vector<string> gListaPalabras; // Ahora se carga dinámicamente
string palabra = "";
string fallidas = "";
int vida = 0;
bool correcta;
bool completa;
int nivel = 1;

// Teclado virtual: letras de la 'a' a la 'z'
const string tecladoVirtual = "abcdefghijklmnopqrstuvwxyz";

// --- CAMBIO: Ahora usa XInput para seleccionar letra ---
char seleccionarLetraJoystick() {
    int indice = 0;
    cout <<  "Usa el stick " << BLACK << BG_YELLOW << "izquierdo" << RESET <<  " para moverte y boton " << BLACK << BG_GREEN<< " A " << RESET << " para seleccionar." << endl;
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
            // Movimiento a la izquierda
            if (x < -16000 && indice > 0) {
                indice--;
                Sleep(200);
            }

            // Mostrar teclado virtual y letra seleccionada
            cout << "\r";
            for (int i = 0; i < tecladoVirtual.size(); ++i) {
                if (i == indice) cout << "[" << tecladoVirtual[i] << "]";
                else cout << " " << tecladoVirtual[i] << " ";
            }
            cout << "   ";

            // Selección con botón A
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
                cout << endl << BLUE << "Letra seleccionada: " << RESET << tecladoVirtual[indice] << endl;
                Sleep(300);
                return tecladoVirtual[indice];
            }
        } else {
            cout << "\nJoystick no conectado. Conectalo y reinicia el juego." << RESET << endl;
            Sleep(1000);
            exit(1);
        }
        Sleep(50);
    }
}

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

// --- CAMBIO: Retorno al menú principal con joystick ---
// FIN CAMBIO

void ihJugarPartida()
{
    srand((int)time(NULL));
    
    auto palabrasConPistas = leerPalabrasConPistas(nivel);
    if (!palabrasConPistas.empty()) {
        cout << MAGENTA << "Palabra: " << RESET << palabrasConPistas[0].first << endl; 
    } else {
        cout << "No hay palabras disponibles para este nivel." << endl;
    }
    if (palabrasConPistas.empty()) {
        cout << BLACK << "No hay palabras cargadas para este nivel." << RESET << endl;
        system("pause");
        return;
    }

    int nroAleatorio = rand() % palabrasConPistas.size();
    string palabraOriginal = palabrasConPistas[nroAleatorio].first;
    string pista = palabrasConPistas[nroAleatorio].second; // Si no hay pista, dejar vacío o asignar según tu lógica
    
    palabra = string(palabraOriginal.size(), '_');
    fallidas = "";


    while (vida > 0)
    {
        ihLimpiarPantalla();
        cout<< MAGENTA << "Bienvenido al juego del ahorcado!"  << RESET << endl;
        cout<< "Nivel: " << nivel << endl;
        ihDibujarAhorcado(vida);
        cout<< YELLOW <<"Pista: " << RESET << pista << endl; // Mostrar pista

        cout<< RED << "Fallos: " << fallidas << RESET << endl;
        cout<< GREEN << "Progreso: " << palabra << RESET << endl;
        cout<< "Selecciona una letra con el joystick:" << endl;
        gOpcion = seleccionarLetraJoystick();

        correcta = false;
        for(int i = 0; i < palabraOriginal.size(); i++) {
            if(tolower(palabraOriginal[i]) == tolower(gOpcion)) {
                palabra[i] = gOpcion;
                correcta = true;
            }
        }

        if (!correcta)
        {
                vida--;
                fallidas += gOpcion;

                // 🔴 Feedback de letra incorrecta
            animacionFeedbackLetra(false);
            }
                else
            {   
                // 🟢 Feedback de letra correcta
            animacionFeedbackLetra(true);
        }

        completa = true;
        for (int i = 0; i < palabra.size(); i++)
        {
            if(palabra[i] == '_')
            {
                completa = false;
            }
        }

        if(completa)
        {
            ihLimpiarPantalla();
            // Mostramos animación de victoria antes del mensaje final
            animacionVictoria();
            cout<< BLUE << BG_CYAN << "::: A H O R C A D O :::" << RESET << endl;
            cout<< LGREEN << "Felicidades, has ganado!" << RESET <<  endl;
            cout << BLUE << "La palabra era: " << RESET <<  gListaPalabras[nroAleatorio] << endl;
            // **AQUÍ**: ANTES DE PAUSAR, LLAMAMOS LA ANIMACION ENTRE PARTIDAS
            animacionCargaEntrePartidas();
            // CAMBIO: Esperar botón A en vez de ENTER
            esperarBotonA("Presiona " + string(BLACK) + BG_GREEN + " A " + RESET + " para volver al menu principal...");
            // FIN CAMBIO
            return;
        }
    }

    ihLimpiarPantalla();
    // Llamamos la animación de derrota justo antes de mostrar el mensaje final
    animacionDerrota();
    cout<< CYAN << BG_BLUE << "::: A H O R C A D O :::" << RESET << endl;
    cout<< RED << "Perdiste" << RESET << endl;
    cout<< BLUE << "La palabra era: " << RESET <<  gListaPalabras[nroAleatorio] << endl;
    // **AQUÍ**: ANTES DE PAUSAR, LLAMAMOS LA ANIMACION ENTRE PARTIDAS
    animacionCargaEntrePartidas();
    // CAMBIO: Esperar botón A en vez de ENTER
    esperarBotonA("Presiona " + string(BLACK) + BG_GREEN + " A " + RESET + " para volver al menu principal...");
    // FIN CAMBIO
    return;
}

int seleccionarNivelJoystick() {
    int nivelSeleccionado = 1;
    XINPUT_STATE state;
    DWORD dwResult;
    cout<< "Selecciona el nivel usando el stick izquierdo y boton " << BLACK << BG_GREEN << " A " << RESET << " para confirmar:" << endl;
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

// --- CAMBIO: Menú principal joystick ---
// FIN CAMBIO

int main ()
{
    
    cout << CYAN << "Programa iniciado..." << endl;
    // Aquí llamas a la función para que se ejecute la animación
    animacionCargaInicial();
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    DWORD dwResult = XInputGetState(0, &state);

    if (dwResult != ERROR_SUCCESS) {
        cout << "No se detecto joystick. Conectalo y reinicia el juego." << endl;
        system("pause");
        return 1;
    }
    // MOSTRAR MENÚ ANIMADO SOLO UNA VEZ AL PRINCIPIO
    //animacionMenuPrincipal();  // ← ESTA ES LA NUEVA ANIMACIÓN
    while(true)
    {
        vida = 6;
        ihLimpiarPantalla();
        cout<< YELLOW << "Bienvenido al juego del ahorcado!"  << endl;
        cout<< MAGENTA << ":::: MENU PRINCIPAL ::::"          << RESET << endl;
        
        // CAMBIO: Selección de nivel con joystick
        nivel = seleccionarNivelJoystick();
        gListaPalabras = leerPalabrasPorNivel(nivel);
        cout<< "Presiona boton " << BLACK << BG_GREEN <<  " A " << RESET <<  " para jugar, boton " << BLACK << BG_RED << " B " << RESET << " para salir." << endl;
        bool seleccion = false;
        
        while (!seleccion) {
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            dwResult = XInputGetState(0, &state);
            if (dwResult == ERROR_SUCCESS) {
                if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {
                    // *** Aquí ponemos la animación de transición antes de iniciar la partida ***
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

    system("pause");
}