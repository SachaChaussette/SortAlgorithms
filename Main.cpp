#include "Main.h"

int main()
{
    locale::global(locale("fr_FR"));
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    // On peut choisir quel type de valeur est stock� dans le tableau
    // 
    // Le bool sert � afficher ou non le tableau tri�, il est pr�f�rable
    // de ne pas afficher lorsqu'on veut mesurer des temps ou des op�rations
    // sur une grande taille

    InsertionSortDemo<int>(true);

    return EXIT_SUCCESS;
}