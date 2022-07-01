#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include <ctype.h>

void pig();

namespace juego
{
    const int CANTIDAD_RONDAS = 1; // Versión final debe ser 5 rondas.

    utils::Jugador jugadores[2]; // Dos Jugadores máximo.
    int sigAJugar = -1;

    int lanzarDado()
    {
        return utils::numeroAleatorio(1, 6);
    }

    int primeroEnOrden(int j1[2], int j2[2])
    {
        // Acumulo las tiradas de cada uno, ya que el primer criterio por el cuál determinar el orden.
        int sum1 = j1[0] + j1[1];
        int sum2 = j2[0] + j2[1];

        /**
         * El Algoritmo para determinar el orden, únicamente se complica cuando
         * empatan en acumulados.
         */
        if (sum1 == sum2)
        {
            // Busco el mayor de cada uno.
            int may1 = j1[0] > j1[1] ? j1[0] : j1[1];
            int may2 = j2[0] > j2[1] ? j2[0] : j2[1];

            // Si vuelven a empatar, retorno -1 con lo cual indico que tienen que volver a tirar los dados.
            if (may1 == may2)
                return -1;

            // Si no empataron, devuelvo según quién tiene el mayor número.
            return may1 > may2 ? 0 : 1;
        }

        // Esta parte quizás pudiese simplificar utilizando algun parafernalia, pero me parece mas legible dejarlo así separado.
        return sum1 > sum2 ? 0 : 1;
    }

    void determinarOrdenJugadores()
    {
        utils::cls();

        cout << "\nLanzando dados para " << jugadores[0].alias << ": " << endl;

        for (int i = 0; i < 2; i++)
        {
            jugadores[0].lanzamientoInicial[i] = lanzarDado();
        }

        utils::pintarDados(jugadores[0].lanzamientoInicial);

        cout << "\nLanzando dados para " << jugadores[1].alias << ": " << endl;

        for (int i = 0; i < 2; i++)
        {
            jugadores[1].lanzamientoInicial[i] = lanzarDado();
        }

        utils::pintarDados(jugadores[1].lanzamientoInicial);

        sigAJugar = primeroEnOrden(jugadores[0].lanzamientoInicial, jugadores[1].lanzamientoInicial);

        if (sigAJugar == -1)
        {
            determinarOrdenJugadores();
        }
    }

    void chequearMejorJugador(utils::Jugador *jug)
    {
        cout << pdvMejor << " " << jug->puntajesFinales.pdv;
        if (jug->puntajesFinales.pdv > pdvMejor)
        {
            aliasMejor = jug->alias;
            pdvMejor = jug->puntajesFinales.pdv;
        }
    }

    void calcularMostrarResultados()
    {
        utils::Jugador *jug1 = &jugadores[0];
        utils::Jugador *jug2 = &jugadores[1];

        if (jug1->puntaje > jug2->puntaje)
        {
            jug1->puntajesFinales.masTrufasEnTotal += 5;
        }
        else if (jug2->puntaje > jug1->puntaje)
        {
            jug2->puntajesFinales.masTrufasEnTotal += 5;
        }
        else
        {
            jug1->puntajesFinales.masTrufasEnTotal += 5;
            jug2->puntajesFinales.masTrufasEnTotal += 5;
        }

        jug1->puntajesFinales.cada50Trufas = 1 * (jug1->puntaje / 50);
        jug2->puntajesFinales.cada50Trufas = 1 * (jug2->puntaje / 50);

        jug1->puntajesFinales.porOinks = 2 * jug1->oinks;
        jug2->puntajesFinales.porOinks = 2 * jug2->oinks;

        if (jug1->mayorCantLanzamientosSeguidos > jug2->mayorCantLanzamientosSeguidos)
        {
            jug1->puntajesFinales.porCodicioso += 3;
        }
        else if (jug2->mayorCantLanzamientosSeguidos > jug1->mayorCantLanzamientosSeguidos)
        {
            jug2->puntajesFinales.porCodicioso += 3;
        }
        else
        {
            jug1->puntajesFinales.porCodicioso += 3;
            jug2->puntajesFinales.porCodicioso += 3;
        }

        utils::cls();

        int totales[2];

        jug1->puntajesFinales.pdv = 0;
        jug2->puntajesFinales.pdv = 0;

        jug1->puntajesFinales.pdv += jug1->puntajesFinales.cada50Trufas;
        jug1->puntajesFinales.pdv += jug1->puntajesFinales.masTrufasEnTotal;
        jug1->puntajesFinales.pdv += jug1->puntajesFinales.porCodicioso;
        jug1->puntajesFinales.pdv += jug1->puntajesFinales.porOinks;

        jug2->puntajesFinales.pdv += jug2->puntajesFinales.cada50Trufas;
        jug2->puntajesFinales.pdv += jug2->puntajesFinales.masTrufasEnTotal;
        jug2->puntajesFinales.pdv += jug2->puntajesFinales.porCodicioso;
        jug2->puntajesFinales.pdv += jug2->puntajesFinales.porOinks;

        cout << "+- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+" << endl;
        cout << "+                   Puntajes Finales                        +" << endl;
        cout << "+- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+" << endl;
        cout << " Hito\t\t\t\t" + jug1->alias + "\t\t" + jug2->alias << endl;
        cout << " Más trufas en total\t\t" + std::to_string(jug1->puntajesFinales.masTrufasEnTotal) + "\t\t" + std::to_string(jug2->puntajesFinales.masTrufasEnTotal) << endl;
        cout << " Cada 50 trufas\t\t\t" + std::to_string(jug1->puntajesFinales.cada50Trufas) + "\t\t" + std::to_string(jug2->puntajesFinales.cada50Trufas) << endl;
        cout << " Oinks\t\t\t\t" + std::to_string(jug1->puntajesFinales.porOinks) + "\t\t" + std::to_string(jug2->puntajesFinales.porOinks) << endl;
        cout << " Cerdo codicioso\t\t" + std::to_string(jug1->puntajesFinales.porCodicioso) + "\t\t" + std::to_string(jug2->puntajesFinales.porCodicioso) << endl;
        cout << "+- - - - - - - - - - - - - - - - - - - - - - - - - - - - - -+" << endl;
        cout << "TOTAL\t\t\t\t" + std::to_string(jug1->puntajesFinales.pdv) + "\t\t" + std::to_string(jug2->puntajesFinales.pdv) << endl;

        cout << endl
             << endl;
        utils::pig("EL GANADOR ES " + (jug1->puntajesFinales.pdv > jug2->puntajesFinales.pdv ? jug1->alias : jug2->alias));

        chequearMejorJugador(jug1->puntajesFinales.pdv > jug2->puntajesFinales.pdv ? jug1 : jug2);

        cout << "En 10 segundos volvemos al menú principal" << endl;
        sleep(10);
    }

    void inicializarJugadores()
    {
        for (int i = 0; i < 2; i++)
        {
            jugadores[i].oinks = 0;
            jugadores[i].mayorCantLanzamientosSeguidos = 0;
            jugadores[i].puntaje = 0;
            jugadores[i].rondaActual = 0;
            jugadores[i].puntajesFinales.cada50Trufas = 0;
            jugadores[i].puntajesFinales.masTrufasEnTotal = 0;
            jugadores[i].puntajesFinales.porCodicioso = 0;
            jugadores[i].puntajesFinales.porOinks = 0;
        }
    }

    void jugar()
    {
        int numRonda = 0;
        int cantDados = 2;

        inicializarJugadores();

        // Guardo el Jugador actual.
        utils::Jugador *jug1 = &jugadores[sigAJugar];
        utils::Jugador *jug2 = &jugadores[sigAJugar == 0 ? 1 : 0];

        do
        {
            jug1->rondaActual += 1;
            int cantLanzamientosRondaActual = 0;

            bool seguir = true;

            int acumTotal = 0;

            do
            {
                cantLanzamientosRondaActual += 1;

                int lanzamientos[3];
                int acum = 0;
                int ant = 0;
                bool hayAs = false;
                bool todosAses = false;
                bool todosIguales = true;
                bool hundido = false;
                bool oink = false;
                bool cedePuntos = false;
                bool cedeTurno = false;

                // Coloco en cero todos los lugares, evitando la posible basura que puedan traer.
                lanzamientos[0] = lanzamientos[1] = lanzamientos[2] = 0;

                for (int l = 0; l < cantDados; l++)
                {
                    lanzamientos[l] = lanzarDado();

                    // Determinamos la presencia de Ases.
                    if (lanzamientos[l] == 1)
                    {
                        hayAs = true;
                    }

                    // Si es la primer vuelta, guardamos como anterior al actual.
                    if (ant == 0)
                        ant = lanzamientos[l];

                    /**
                     * Considero que son todos iguales si el anterior y el actual son iguales y no hubo ninguna discrepancia antes (todosIguales sigue en true).
                     * Ej: 1er vuelta -> todosIguales = 20 == 20 && true -> todosIguales = true;
                     *     2da vuelta -> todosIguales = 20 == 30 && true -> todosIguales = false;
                     *     3er vuelta -> todosIguales = 20 == 20 && false -> todosIguales = false;
                     *
                     * Con todosIguales mantenemos el estado de igualdad en todos los tiros. Si finaliza en true
                     * nos indica que nunca hubo una discrepancia en las igualdades.
                     */
                    todosIguales = ant == lanzamientos[l] && todosIguales;
                }

                // Acumulamos los valores de los dados involucrados en el tiro.
                for (int i = 0; i < cantDados; i++)
                    acum += lanzamientos[i];

                /**
                 * Si todos los tiros dieron 1 (As), la suma debería ser igual a la cantidad de dados involucrados.
                 * Ej: 2 dados -> 1 + 1 == 2 | 3 dados -> 1 + 1 + 1 == 3
                 */
                todosAses = acum == cantDados;

                /**
                 * Determinamos que pasa con los puntos obtenidos.
                 */
                // Son todos los dados iguales...
                if (todosIguales)
                {
                    // y son ases
                    if (todosAses)
                    {
                        // El cerdo se hunde en el barro...
                        if (cantDados == 3)
                        {
                            // Cede todos sus puntos al cerdo 2 por jugar con 3 dados...
                            jug2->puntaje += jug1->puntaje;
                            cedePuntos = true;
                        }

                        // pierde todos los puntos actuales y acumulados...
                        acum = 0;
                        acumTotal = 0;
                        jug1->puntaje = 0;
                        // Cede automaticamente el turno.
                        seguir = false;
                        hundido = true;
                        // Al hundirse en el barro, se pasa a jugar con 3 dados.
                        cantDados = 3;
                    }
                    else
                    {
                        // Todos iguales pero no ases...El cerdo hace OINK y acumula el doble. Acumula el doble.
                        acum *= 2;
                        jug1->oinks += 1;
                    }
                }
                else
                {
                    // Las caras son distintas, pero hay un as.
                    if (hayAs)
                    {
                        acum = 0;
                        acumTotal = 0;
                        seguir = false;
                        cedeTurno = true;
                    }
                }

                acumTotal += acum;

                utils::cls();
                cout << jugadores[0].alias << ": " << jugadores[0].puntaje << " trufas acumuladas.\t";
                cout << jugadores[1].alias << ": " << jugadores[1].puntaje << " trufas acumuladas." << endl;

                cout << "\nTURNO DE " << jug1->alias << "\n"
                     << endl;

                cout << "+--------------------------+" << endl;
                cout << " RONDAS # " << jug1->rondaActual << endl;
                cout << " TRUFAS DE LA RONDA : " << acumTotal << endl;
                cout << " LANZAMIENTOS : " << cantLanzamientosRondaActual - 1 << endl;
                cout << "+--------------------------+\n"
                     << endl;

                cout << "LANZAMIENTO # " << cantLanzamientosRondaActual << "\n"
                     << endl;

                utils::pintarDados(lanzamientos);
                cout << endl;

                if (acum > 0)
                {
                    cout << "ACUMULASTE " << acum << " TRUFAS EN ESTE LANZAMIENTO !!!";
                }

                cout << endl;

                /**
                 * El jugador actual puede decidir si continúa
                 * únicamente cuando no haya caido en alguna de las penalizaciones.
                 */
                if (seguir)
                {
                    char resp = 'N';

                    cout << "¿Continuar? (S/N): ";
                    cin >> resp;

                    resp = toupper(resp);

                    seguir = resp == 'S';
                }

                // Acá ya sea por decisión del usuario o por penalización, se cambia de jugador.
                if (!seguir)
                {
                    if (hundido || cedeTurno)
                    {
                        string str = "";

                        if (hundido)
                        {
                            str = "TE HAS HUNDIDO EN EL BARRO Y PIERDES TUS PUNTOS...";
                            if (cedePuntos)
                                str += " Y SON CEDIDOS AL JUGADOR " + jug2->alias;
                        }
                        else if (cedeTurno)
                        {
                            str = "HAS PERDIDO EL TURNO!!";
                        }

                        utils::pig(str);

                        if (jug1->rondaActual < 5 && jug2->rondaActual < 5)
                        {
                            cout << "En 3 segundos continuamos con el próximo tiro..." << endl;
                            sleep(3);
                        }
                    }

                    if (jug1->mayorCantLanzamientosSeguidos < cantLanzamientosRondaActual)
                        jug1->mayorCantLanzamientosSeguidos = cantLanzamientosRondaActual;

                    // Acumulo los puntos acumulados en la ronda si los hubiese.
                    jug1->puntaje += acumTotal;

                    // Intercambio quién continua.
                    sigAJugar = sigAJugar == 0 ? 1 : 0;

                    // Piso los valores referenciados.
                    jug1 = &jugadores[sigAJugar];
                    jug2 = &jugadores[sigAJugar == 0 ? 1 : 0];
                }

                if (cantDados == 2 && (jug1->puntaje >= 50 || jug2->puntaje >= 50))
                {
                    cantDados = 3;
                }

            } while (seguir);

            seguir = true;

        } while (jug1->rondaActual < 5 || jug2->rondaActual < 5);

        calcularMostrarResultados();
    }

    void main()
    {
        utils::pig("Comenzamos a Jugar! Primero ingresa los nombre de los jugadores...");

        cout << "Ingrese el alias del primer jugador: ";
        cin >> jugadores[0].alias;
        jugadores[0].alias = utils::toUpper(jugadores[0].alias);
        jugadores[0].puntaje = 0;
        jugadores[0].rondaActual = 0;

        cout << "Ingrese el alias del segundo jugador: ";
        cin >> jugadores[1].alias;
        jugadores[1].alias = utils::toUpper(jugadores[1].alias);
        jugadores[1].puntaje = 0;
        jugadores[1].rondaActual = 0;

        determinarOrdenJugadores();

        cout << "\nComienza " << jugadores[sigAJugar].alias << "!!!" << endl;

        char opc;

        cout << "¿Comenzamos? (S/N): ";
        cin >> opc;

        if (toupper(opc) != 'S')
            return;

        utils::cls();

        jugar();
    }
} // namespace juego
