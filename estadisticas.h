#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

namespace estadisticas
{

    void main()
    {
        cout << utils::ESTADISTICAS_TITULO << endl;

        cout << "\nMEJOR CHANCHO\n"
             << endl;
        cout << "Alias: \t\t" + aliasMejor << endl;
        cout << "PDVs: \t\t" + std::to_string(pdvMejor) << endl;

        sleep(10);
    }

} // namespace estadisticas