#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <SDL.h>

using namespace std;

// Prototipos de funciones
void categorias();
void ingresoCategoria(int op);
void empezarJuego(const vector<string>& palabras, const string& nombre);
void dibujo(int intentos);
char seleccionarLetraConJoystick();

// Función principal
int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_GAMECONTROLLER) < 0) {
        cout << "No se pudo inicializar SDL: " << SDL_GetError() << endl;
        return 1;
    }
    categorias();
    SDL_Quit();
    system("pause");
    return 0;
}

// Imprime las categorías y permite elegir una
void categorias() {
    int op;
    do {
        system("cls");
        cout << "\n\t\t\t\tJUEGO EL AHORCADO\n\n";
        cout << " CATEGORIAS\n\n";
        cout << " 1. Frutas\n";
        cout << " 2. Animales\n";
        cout << " 3. Paises\n";
        cout << " 4. Objetos\n\n";
        cout << " Ingresa una opcion: ";
        cin >> op;
    } while (op < 1 || op > 4);

    ingresoCategoria(op);
}

// Recibe la opción y llama a la función para empezar el juego
void ingresoCategoria(int op) {
    vector<string> nombrecat = {"Frutas", "Animales", "Paises", "Objetos"};
    vector<string> frutas = {"MELON", "PAPAYA", "SANDIA", "MANZANA", "PERA", "NARANJA", "UVA", "CEREZA", "CIRUELA", "KIWI"};
    vector<string> animales = {"PERRO", "GATO", "CABALLO", "GALLINA", "JIRAFA", "MONO", "VACA", "CONEJO", "TORTUGA", "LOBO"};
    vector<string> paises = {"PERU", "COLOMBIA", "ARGENTINA", "NICARAGUA", "ITALIA", "MEXICO", "CANADA", "VENEZUELA", "ECUADOR", "BRASIL"};
    vector<string> objetos = {"MOCHILA", "RELOJ", "ZAPATILLA", "MUEBLE", "CUADERNO", "SILLA", "MESA", "CELULAR", "PUERTA", "AURICULARES"};

    switch (op) {
        case 1:
            empezarJuego(frutas, nombrecat[op - 1]);
            break;
        case 2:
            empezarJuego(animales, nombrecat[op - 1]);
            break;
        case 3:
            empezarJuego(paises, nombrecat[op - 1]);
            break;
        case 4:
            empezarJuego(objetos, nombrecat[op - 1]);
            break;
    }
}

// Algoritmo principal del juego
void empezarJuego(const vector<string>& palabras, const string& nombre) {
    srand((unsigned)time(0));
    int opcion = rand() % palabras.size();
    string palabra = palabras[opcion];
    int longitud = palabra.length();
    string frase(longitud, '_');
    int puntos = 1200;
    int intentos = 0;
    int aciertos = 0;

    do {
        aciertos = 0;
        system("cls");
        cout << "\n\t\t\t\tJUEGO EL AHORCADO\n\n";
        cout << " CATEGORIA: " << nombre << "\n\n";
        cout << " Intentos Disponibles: " << 6 - intentos << "\t\t\t\tPuntuacion: " << puntos << "\n\n";
        dibujo(intentos);

        cout << "\n\n\n";
        for (char c : frase) cout << " " << c << " ";
        cout << endl;

        if (intentos == 6) {
            cout << "\n\n PERDISTE!!\n";
            cout << " LA SOLUCION ERA: " << palabra << "\n\n";
            cout << " Presiona ENTER para volver a jugar..";
            cin.ignore();
            cin.get();
            categorias();
            return;
        }

        // Comprobar si se ha adivinado la palabra
        int espacios = 0;
        for (char c : frase)
            if (c == '_') espacios++;

        if (espacios == 0) {
            cout << "\n\n FELICIDADES.. GANASTE!!\n\n";
            cout << " Presiona ENTER para volver a jugar..";
            cin.ignore();
            cin.get();
            categorias();
            return;
        }

        // Selección de letra con joystick
        char letra = seleccionarLetraConJoystick();

        // Verifica si la letra existe en la palabra
        for (int j = 0; j < longitud; j++) {
            if (letra == palabra[j] && frase[j] == '_') {
                frase[j] = letra;
                aciertos++;
            }
        }

        if (aciertos == 0) {
            intentos++;
            puntos -= 200;
        }

    } while (intentos != 7);

    cout << "\n\n";
}

// Dibuja el ahorcado según los intentos
void dibujo(int intentos) {
    switch (intentos) {
        case 0:
            cout << "\n     _______\n    |       |\n    |\n    |\n    |\n    |\n    |\n ----------";
            break;
        case 1:
            cout << "\n     _______\n    |       |\n    |       0\n    |\n    |\n    |\n    |\n ----------";
            break;
        case 2:
            cout << "\n     _______\n    |       |\n    |       0\n    |       |\n    |\n    |\n    |\n ----------";
            break;
        case 3:
            cout << "\n     _______\n    |       |\n    |       0\n    |      /|\n    |\n    |\n    |\n ----------";
            break;
        case 4:
            cout << "\n     _______\n    |       |\n    |       0\n    |      /|\\\n    |\n    |\n    |\n ----------";
            break;
        case 5:
            cout << "\n     _______\n    |       |\n    |       0\n    |      /|\\\n    |      /\n    |\n    |\n ----------";
            break;
        case 6:
            cout << "\n     _______\n    |       |\n    |       0\n    |      /|\\\n    |      / \\\n    |\n    |\n ----------";
    }
}

// Teclado virtual: selecciona letra con joystick o flechas
char seleccionarLetraConJoystick() {
    SDL_GameController* controller = nullptr;
    for (int i = 0; i < SDL_NumJoysticks(); ++i) {
        if (SDL_IsGameController(i)) {
            controller = SDL_GameControllerOpen(i);
            break;
        }
    }

    const int num_letras = 26;
    int seleccion = 0;
    bool seleccionada = false;

    while (!seleccionada) {
        system("cls");
        cout << "\nSelecciona una letra con el joystick (D-Pad) o flechas y pulsa A/Enter para elegir:\n\n";
        for (int i = 0; i < num_letras; ++i) {
            if (i == seleccion)
                cout << "[" << char('A' + i) << "] ";
            else
                cout << " " << char('A' + i) << "  ";
        }
        cout << endl;

        SDL_Event e;
        bool moved = false;
        Uint32 start = SDL_GetTicks();
        while (SDL_GetTicks() - start < 200) { // Espera 200ms para evitar rebotes
            while (SDL_PollEvent(&e)) {
                if (e.type == SDL_CONTROLLERBUTTONDOWN && controller) {
                    if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_RIGHT) {
                        seleccion = (seleccion + 1) % num_letras;
                        moved = true;
                    }
                    if (e.cbutton.button == SDL_CONTROLLER_BUTTON_DPAD_LEFT) {
                        seleccion = (seleccion - 1 + num_letras) % num_letras;
                        moved = true;
                    }
                    if (e.cbutton.button == SDL_CONTROLLER_BUTTON_A) {
                        seleccionada = true;
                    }
                }
                // Permitir usar teclado si no hay mando
                if (e.type == SDL_KEYDOWN) {
                    if (e.key.keysym.sym == SDLK_RIGHT) {
                        seleccion = (seleccion + 1) % num_letras;
                        moved = true;
                    }
                    if (e.key.keysym.sym == SDLK_LEFT) {
                        seleccion = (seleccion - 1 + num_letras) % num_letras;
                        moved = true;
                    }
                    if (e.key.keysym.sym == SDLK_RETURN) {
                        seleccionada = true;
                    }
                }
            }
            if (moved) break;
            SDL_Delay(10);
        }
    }

    if (controller) SDL_GameControllerClose(controller);
    return char('A' + seleccion);
}