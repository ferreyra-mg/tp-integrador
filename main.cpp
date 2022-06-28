#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <time.h>
#include <ctype.h>

#include "globales.h"
#include "utils.h"
#include "creditos.h"
#include "estadisticas.h"
#include "juego.h"

using namespace std;
using namespace utils;

void procesarOpcionMenu(int opc);
void menuPrincipal();

string aliasMejor = "";
int pdvMejor = 0;

void consultarSalida()
{
    char respuesta;

    cout << "¿Salir del Juego? (S/N): ";
    cin >> respuesta;

    switch (toupper(respuesta))
    {
    case 'N':
        menuPrincipal();
        break;
    case 'S':
        utils::cls();
        utils::pig("Hasta pronto!");
        break;
    default:
        procesarOpcionMenu(-1);
        break;
    }
}

void procesarOpcionMenu(int opc)
{
    utils::cls();

    switch (opc)
    {
    case 1:
        juego::main();
        break;
    case 2:
        estadisticas::main();
        break;
    case 3:
        creditos::main();
        break;
    default:
        return consultarSalida();
        break;
    }

    cin.get();
    menuPrincipal();
}

void menuPrincipal()
{
    srand(time(NULL));

    bool valido = false;
    int opc = -1;

    do
    {
        valido = false;
        opc = -1;

        utils::cls();
        cout << TITULO_GENERAL << endl;
        cout << "-------------------------" << endl;
        cout << "1 - JUGAR" << endl;
        cout << "2 - ESTADISTICAS" << endl;
        cout << "3 - CERDITOS" << endl;
        cout << "-------------------------" << endl;
        cout << "0 - SALIR" << endl;

        cin >> opc;

        valido = opc >= 0 && opc <= 3; // XXX: falla si se pone una letra.
    } while (!valido);

    procesarOpcionMenu(opc);
}

int main(void)
{
    menuPrincipal();
    return 0;
}