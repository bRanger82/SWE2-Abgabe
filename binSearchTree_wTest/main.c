#include <stdio.h>
#include <stdlib.h>
#include "TestProgram.h"


int main(void)
{
    printf("Bitte Anzahl der Testwerte eingeben: (zwischen 2 und 50)\n");
    int cnt = getNumberFromStdIn();
    if (cnt < 2 || cnt > 50)
    {
        printf("Fehler: Zahl liegt nicht zwischen 2 und 50!\n");
        return EXIT_FAILURE;
    }

    KNOTEN * wurzel = createTestValues(cnt, false);
    if (NULL == wurzel)
    {
        printf("Fehler: Baum konnte nicht erstellt werden\n");
        return EXIT_FAILURE;
    }

    printOrder(wurzel);

    printf("Bitte geben Sie die Zahl ein nach der Sie suchen wollen: (groesser 0):\n");
    int searchVal = getNumberFromStdIn();
    if (searchVal != 0)
        searchValue(wurzel, searchVal);

    freeTree(wurzel);

    return EXIT_SUCCESS;
}
