#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

namespace utils
{
    const char *TITULO_GENERAL = R"( _____  _       _____ ______   ___   _   _   _____  _____ ______ ______  _____ 
|  ___|| |     |  __ \| ___ \ / _ \ | \ | | /  __ \|  ___|| ___ \|  _  \|  _  |
| |__  | |     | |  \/| |_/ // /_\ \|  \| | | /  \/| |__  | |_/ /| | | || | | |
|  __| | |     | | __ |    / |  _  || . ` | | |    |  __| |    / | | | || | | |
| |___ | |____ | |_\ \| |\ \ | | | || |\  | | \__/\| |___ | |\ \ | |/ / \ \_/ /
\____/ \_____/  \____/\_| \_|\_| |_/\_| \_/  \____/\____/ \_| \_||___/   \___/                                                                                
)";

    const char *CERDITOS_TITULO = R"( _____  _____ ______ ______  _____  _____  _____  _____ 
/  __ \|  ___|| ___ \|  _  \|_   _||_   _||  _  |/  ___|
| /  \/| |__  | |_/ /| | | |  | |    | |  | | | |\ `--. 
| |    |  __| |    / | | | |  | |    | |  | | | | `--. \
| \__/\| |___ | |\ \ | |/ /  _| |_   | |  \ \_/ //\__/ /
 \____/\____/ \_| \_||___/   \___/   \_/   \___/ \____/                                                         
)";

    const char *ESTADISTICAS_TITULO = R"( _____  _____  _____   ___  ______  _  _____  _____  _____  _____   ___   _____ 
|  ___|/  ___||_   _| / _ \ |  _  \(_)/  ___||_   _||_   _|/  __ \ / _ \ /  ___|
| |__  \ `--.   | |  / /_\ \| | | | _ \ `--.   | |    | |  | /  \// /_\ \\ `--. 
|  __|  `--. \  | |  |  _  || | | || | `--. \  | |    | |  | |    |  _  | `--. \
| |___ /\__/ /  | |  | | | || |/ / | |/\__/ /  | |   _| |_ | \__/\| | | |/\__/ /
\____/ \____/   \_/  \_| |_/|___/  |_|\____/   \_/   \___/  \____/\_| |_/\____/_
)";

    const char *CARITA = R"(
        ¯\_(ツ)_/¯
    )";

    struct PuntajesFinales
    {
        int masTrufasEnTotal;
        int cada50Trufas;
        int porOinks;
        int porCodicioso;
        int pdv;
    };

    struct Marcas
    {
        char masTrufasEnTotal;
        char cada50Trufas;
        char porOinks;
        char porCodicioso;
        char pdv;
    };

    struct Jugador
    {
        string alias;
        int puntaje;
        int lanzamientoInicial[2];
        int rondaActual;
        int mayorCantLanzamientosSeguidos;
        int oinks;
        PuntajesFinales puntajesFinales;
        int mayorCantidadTrufasEnUnLanzamiento;
        Marcas marcas;
    };

    void pig(string msg = "")
    {
        if (msg.length() > 0)
        {
            string lineaAbajo = "";

            for (int i = 0; i < msg.length(); i++)
            {
                lineaAbajo += "_";
            }

            cout << "    | " << msg << " |" << endl;

            cout << "     \\" << lineaAbajo << "/" << endl;
            cout << "    /" << endl;
        }
        cout << "  ,,__" << endl;
        cout << "c''    )?" << endl;
        cout << "   w w" << endl;
    }

    string toUpper(string str)
    {
        string temp = str;

        for (int i = 0; i < temp.length(); i++)
        {
            temp[i] = toupper(temp[i]);
        }

        return temp;
    }

    void pintarPisoTechoDados(int vec[])
    {

        for (int i = 0; i < 13; i++)
        {
            cout << (i % 2 == 0 ? " " : "+");
        }

        cout << "  ";

        for (int i = 0; i < 13; i++)
        {
            cout << (i % 2 == 0 ? " " : "+");
        }

        if (vec[2] > 0)
        {
            cout << "  ";
            for (int i = 0; i < 13; i++)
            {
                cout << (i % 2 == 0 ? " " : "+");
            }
        }

        cout << endl;
    }

    void pintarDados(int nums[])
    {
        // // int nums[3];
        // nums[0] = 6;
        // nums[1] = 5;
        // nums[2] = 4;

        pintarPisoTechoDados(nums);

        for (int i = 0; i < 5; i++)
        {
            for (int w = 0; w < 3; w++)
            {
                int num = nums[w];

                if (num > 0)
                {
                    for (int x = 0; x < 13; x++)
                    {
                        if (x == 0 || x == 12)
                        {
                            cout << "+";
                        }
                        else if ((num == 1 || num == 5) && i == 2 && (x == 6))
                        {
                            cout << "X";
                        }
                        else if (num == 3 && x == 6 && i == 2)
                        {
                            cout << "X";
                        }
                        else if ((num == 2 || num == 3 || num == 4 || num == 5 || num == 6) && ((i == 0 && x == 9) || (i == 4 && x == 3)))
                        {
                            cout << "X";
                        }
                        else if ((num == 4 || num == 5 || num == 6) && ((i == 0 && x == 3) || (i == 4 && x == 9)))
                        {
                            cout << "X";
                        }
                        else if (num == 6 && (i == 2 && (x == 3 || x == 9)))
                        {
                            cout << "X";
                        }
                        else
                        {
                            cout << " ";
                        }
                    }
                }

                cout << "  ";
            }
            cout << endl;
        }

        pintarPisoTechoDados(nums);
    }

    void dados()
    {
        cout << " + + + + + + " << endl;
        cout << "+  O     O  +" << endl;
        cout << "+           +" << endl;
        cout << "+  O     O  +" << endl;
        cout << "+           +" << endl;
        cout << "+  O     O  +" << endl;
        cout << " + + + + + + " << endl;
    }

    void pausar(string msg = "")
    {
        int tecla = 0;

        cout << msg << endl;

        tecla = cin.get();
    }

    void pausaVolverMenuPrincipal()
    {
        pausar("\n\n\nPresione cualquier tecla para volver al Menu Principal");
    }

    void cls()
    {
#if defined _WIN32
        system("cls");
        // clrscr(); // including header file : conio.h
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
        system("clear");
        // std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined(__APPLE__)
        system("clear");
#endif
    }

    int numeroAleatorio(int min = 1, int max = 6)
    {
        return min + rand() % max;
    }
}