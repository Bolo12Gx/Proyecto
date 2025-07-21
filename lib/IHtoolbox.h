#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <fstream>
#include <windows.h> // Para usar Sleep en Windows
using namespace std;

char iden = ','; // Ubicar este identificador en mis archivos de utilidad.
                    // Este identificador se utiliza para separar los campos en el archivo .csv 
                    // Asi no quemo al separador cuando quiera cmabiar la forma de saber hasta donde termina un elemento.

#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_BLUE    "\033[34m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN    "\033[36m"

vector<string> splitString(const string& s,const char iden) // Recibo una cadena string llamada s y un caracter iden que es el separador.
{
    vector<string> tokens; // Aqui se guardarán los tokens separados por el caracter iden.
    string token; // Aqui estará cada palabra econtrada
    size_t start = 0;
    size_t end = s.find(iden); // busca la posicion del primer iden en la cadena s

    while (end != string::npos) { // Mientras encuentre el iden en la cadena s
                                // Recuerda que end fue el nombre que le diste a la posicion de la primera coma en la cadena s.
                                // si s.find no la encientra, devuelve string::npos, que es un numero gigantesco (el mayor de un size_t).
                                // Si npos es verdadero, el (!) lo vuelve falso y sale del while.

        token = s.substr(start, end - start);
        tokens.push_back(token);
        start = end + 1;
        end = s.find(iden, start);
    }
    tokens.push_back(s.substr(start)); 
    return tokens;
}

int getConsoleNumero(const string& mensaje = "Ingrese un numero: ", int minimo = 0, int maximo = 10) {
    int valor;
    string entrada;
    while (true) {
        cout << mensaje;
        getline(cin, entrada); // Lee toda la línea como string
        try {
            valor = stoi(entrada); // Intenta convertir a int
            if (valor >= minimo && valor <= maximo)
                break;
            else
                cout << ":( Valores entre " << minimo << " y " << maximo << endl;
        } catch (...) {
            cout << ":( Ingrese solo numeros validos entre " << minimo << " y " << maximo << endl;
        }
    }
    return valor;
}

string getConsoleCadena(const string& mensaje = "Ingrese una cadena: ") {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

string showSpinner(const string msg = "")
{
    string spinner      = "|/-|\\";
    size_t spinnerLength= spinner.length();

    for (size_t i = 0; i <= 100; i++)
    {
        cout<<"\r" << spinner[i%spinnerLength] << " " << i << " % " + msg;
        Sleep(90);
    }
    cout.flush();
    return "";
}
string showWaiting(const string msg = "")
{
    vector<string> animacion= {"0oo","o0o","oo0","o0o"};
    size_t  animacionLength = animacion.size();

    for (size_t i = 0; i <= 20; i++)
    {
        cout<<"\r" << animacion[i%animacionLength] << " ... " + msg;
        Sleep(100);
    }
    cout.flush();
    return "";
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

void ihLimpiarPantalla() 
{
    system("cls");
}