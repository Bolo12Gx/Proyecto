#include <iostream>
#include "../lib/color.h" 
#include <ctime>


using namespace std;

void ihDibujarAhorcado(int vida)
{
    
    switch(vida)
    {
        case 6:
            cout << "  +---+\n"
                    "  |   |\n"
                    "      |\n"
                    "      |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n"<< RESET;

            break;
        case 5:
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    "      |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n";
            break;
        case 4:
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    "  |   |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n";
            break;
        case 3:
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    " /|   |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n";
            break;
        case 2:
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    " /|\\  |\n"
                    "      |\n"
                    "      |\n"
                    "=========\n";
            break;
        case 1:
            cout << "  +---+\n"
                    "  |   |\n"
                    "  O   |\n"
                    " /|\\  |\n"
                    " /    |\n"
                    "      |\n"
                    "=========\n";
            break;
        case 0:
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