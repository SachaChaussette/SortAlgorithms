#include "Main.h"

int main()
{
    locale::global(locale("fr_FR"));
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // On peut choisir quel type de valeur est stocké dans le tableau
    // 
    // Le bool sert à afficher ou non le tableau trié, il est préférable
    // de ne pas afficher lorsqu'on veut mesurer des temps ou des opérations
    // sur une grande taille

    InsertionSortDemo<int>(true);

    return EXIT_SUCCESS;
}