#include <windows.h>
#include <Xinput.h>
#include <iostream>
#include <ctime>
#include <string>
#include "../lib/animaciones.h"
#include "../lib/dibujo.h"
#include "filewords.cpp" // Para leerPalabrasPorNivel
#include "../lib/color.h"

//c++ src/main.cpp -o output/main.exe -lXinput9_1_0

#pragma comment(lib, "Xinput9_1_0.lib")

using namespace std;

char opcion = ' ';

vector<string> listaPalabras; // Ahora se carga dinámicamente
string palabra = "";
string fallidas = "";
int vida = 0;
bool correcta;
bool completa;
int nivel = 1;

// Teclado virtual: letras de la 'a' a la 'z'
const string tecladoVirtual = "abcdefghijklmnopqrstuvwxyz";

/**
 * @brief Permite al usuario seleccionar una letra usando el joystick.
 *
 * Muestra un teclado virtual en pantalla y permite navegar con el stick izquierdo.
 * El usuario selecciona una letra con el botón A. Si presiona el botón B, retorna '\0' para indicar que desea regresar al menú principal.
 * @return La letra seleccionada, o '\0' si se presionó el botón B.
 */
char seleccionarLetraJoystick() {
    int indice = 0;
    cout <<  "\nUsa el stick " << BLACK << BG_YELLOW << "izquierdo" << RESET <<  " para moverte y boton " << BLACK << BG_GREEN<< " A " << RESET << " para seleccionar." << endl;
    cout << CYAN << "\nPresiona boton " << BLACK << BG_RED << " B " << RESET << " para regresar al menu principal." << endl;
    while (true) {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD dwResult = XInputGetState(0, &state);

        if (dwResult == ERROR_SUCCESS) {
            SHORT x = state.Gamepad.sThumbLX;
            if (x > 16000 && indice < tecladoVirtual.size() - 1) {
                indice++;
                Sleep(200);
            }
            if (x < -16000 && indice > 0) {
                indice--;
                Sleep(200);
            }

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
/**
 * @brief Espera hasta que el usuario presione el botón B en el joystick.
 *
 * Muestra un mensaje en pantalla y entra en un bucle hasta que se detecta el botón B presionado.
 * @param mensaje Mensaje que se muestra al usuario mientras espera.
 */
void esperarBotonB(const string& mensaje) 
{
    cout << mensaje << endl;
    while (true) 
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD dwResult = XInputGetState(0, &state);
        if (dwResult == ERROR_SUCCESS) 
        {
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B)
             {
                Sleep(300);
                break;
            }
        }
    }
}
// --- CAMBIO: Retorno al menú principal con joystick ---
// FIN CAMBIO
/**
 * @brief Ejecuta una partida del juego del ahorcado.
 *
 * Muestra la palabra oculta, la pista y el progreso del jugador. Permite seleccionar letras con el joystick.
 * Si el usuario presiona el botón B, regresa al menú principal. Muestra animaciones de victoria o derrota según el resultado.
 * No recibe parámetros ni retorna valores.
 */

void jugarPartida()
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
    DibujarAhorcado(vida);
    cout<< YELLOW <<"Pista: " << RESET << pista << endl; // Mostrar pista
    


    while (vida > 0)
    {
        limpiarPantalla();
        cout<< MAGENTA << "Bienvenido al juego del ahorcado!"  << RESET << endl;
        cout<< "Nivel: " << nivel << endl;
        DibujarAhorcado(vida);
        cout<< YELLOW <<"Pista: " << RESET << pista << endl; // Mostrar pista

        cout << GREEN << "\nProgreso: ";
        for (char c : palabra) 
            cout << c << "  "; // Dos espacios entre letras
        cout << RESET << endl;

        cout << RED << "\nFallos: ";

        for (char c : fallidas)
            cout << c << "  "; // Dos espacios entre letras fallidas
        cout << RESET << endl;

        cout<< "\nSelecciona una letra con el joystick:" << endl;
        opcion = seleccionarLetraJoystick();
        if (opcion == '\0')
        {
            animarCargaEntrePartidas();
            return; // Regresa al menú principal
        }

        bool letraYaUsada = false;
        for (char c : palabra) {
            if (tolower(c) == tolower(opcion))
            {
                letraYaUsada = true;
                break;
            }
        }
        if (!letraYaUsada) 
        {
            for (char c : fallidas) 
            {
                if (tolower(c) == tolower(opcion)) 
                {
                    letraYaUsada = true;
                    break;
                }
            }
        }

        if (letraYaUsada) {
            cout << RED << "\nYa usaste esa letra! Elige otra." << RESET << endl;
            Sleep(1200); // Espera un momento para que el usuario vea el mensaje
            continue;    // Vuelve a pedir letra
        }
        correcta = false;
        for(int i = 0; i < palabraOriginal.size(); i++) {
            if(tolower(palabraOriginal[i]) == tolower(opcion)) {
                palabra[i] = opcion;
                correcta = true;
            }
        }

        if (!correcta)
        {
            vida--;
            fallidas += opcion;
        }

        // --- MODIFICACIÓN: Verificar si la palabra está completa dentro del ciclo ---
        completa = true;
        for (int i = 0; i < palabra.size(); i++)
        {
            if(palabra[i] == '_')
                completa = false;
        }
        if (completa)
        {
            limpiarPantalla();
            // Mostramos animación de victoria antes del mensaje final

            mostrarVictoria();

            cout<< BLUE << BG_CYAN << "::: A H O R C A D O :::" << RESET << endl;
            mostrarAhorcadoSaltando();
            cout << BLUE << "La palabra era: " << RESET <<  listaPalabras[nroAleatorio] << endl;

            animarCargaEntrePartidas();

            mostrarCreditos();
            Sleep(500);

            esperarBotonB("Presiona " + string(BLACK) + BG_GREEN + " B " + RESET + " para volver al menu principal...");

            return;
        }
        // --- FIN MODIFICACIÓN ---
    }
    
    limpiarPantalla();
    // Llamamos la animación de derrota justo antes de mostrar el mensaje final
    mostrarDerrota();
    cout<< CYAN << BG_BLUE << "::: A H O R C A D O :::" << RESET << endl;
    cout << "  +---+\n"
        "  |   |\n"
        "  O   |\n"
        " /|\\  |\n"
        " / \\  |\n"
        "      |\n"
        "=========\n";
    cout<< RED << "Perdiste" << RESET << endl;
    cout<< BLUE << "La palabra era: " << RESET <<  listaPalabras[nroAleatorio] << endl;

    animarCargaEntrePartidas();

    mostrarCreditos();
    Sleep(500);

    esperarBotonB("\nPresiona " + string(BLACK) + BG_GREEN + " B " + RESET + " para volver al menu principal...");

    return;
}
/**
 * @brief Permite al usuario seleccionar el nivel de dificultad usando el joystick.
 *
 * Muestra los niveles disponibles y permite navegar con el stick izquierdo. El usuario confirma el nivel con el botón A.
 * @return El número de nivel seleccionado.
 */
int seleccionarNivelJoystick() 
{
    int nivelSeleccionado = 1;
    XINPUT_STATE state;
    DWORD dwResult;
    cout<< "\nSelecciona el nivel usando el stick izquierdo y boton " << BLACK << BG_GREEN << " A " << RESET << " para confirmar:" << endl;
    bool nivelElegido = false;
    while (!nivelElegido) 
    {
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
            if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) 
            {
                Sleep(300);
                nivelElegido = true;
            }
        }
        Sleep (50);
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
    mostrarSpinner();
    XINPUT_STATE state;
    ZeroMemory(&state, sizeof(XINPUT_STATE));
    DWORD dwResult = XInputGetState(0, &state);

    if (dwResult != ERROR_SUCCESS) {
        cout << "No se detecto joystick. Conectalo y reinicia el juego." << endl;
        system("pause");
        return 1;
    }
    // MOSTRAR MENÚ ANIMADO SOLO UNA VEZ AL PRINCIPIO
    animarMenu();  // ← ESTA ES LA NUEVA ANIMACIÓN
    while(true)
    {
        vida = 6;
        limpiarPantalla();
        cout<< YELLOW << "Bienvenido al juego del ahorcado!"  << endl;
        cout<< MAGENTA << ":::: MENU PRINCIPAL ::::"          << RESET << endl;
        
        // Selección de nivel con joystick
        nivel = seleccionarNivelJoystick();
        listaPalabras = leerPalabrasPorNivel(nivel);
        
        cout << "Presiona boton " << BLACK << BG_GREEN << " A " << RESET 
             << " para jugar, boton " << BLACK << BG_RED << " B " << RESET << " para salir." << endl;
        
        bool seleccion = false;
        
        while (!seleccion) 
        {
            ZeroMemory(&state, sizeof(XINPUT_STATE));
            dwResult = XInputGetState(0, &state);
            if (dwResult == ERROR_SUCCESS) {
                if (state.Gamepad.wButtons & XINPUT_GAMEPAD_A) {

                    // *** Aquí ponemos la animación de transición antes de iniciar la partida ***
                    animarTransicionNivel();

                    jugarPartida();
                    seleccion = true;
                }
                if (state.Gamepad.wButtons & XINPUT_GAMEPAD_B) {
                    cout << MAGENTA << "Gracias por jugar!" << RESET << endl;
                    mostrarCreditos();
                    Sleep(1000);
                    return 0;
                }
            } else {
                cout << "Joystick desconectado." << endl;
                return 1;
            }
            Sleep(100);
        }
    }
}