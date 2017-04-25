#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TestProgram.h"

int selectAndRunTests(void);

int main()
{
    int returnTestValue = selectAndRunTests();
    return returnTestValue;
}

int selectAndRunTests(void)
{
    char str[255];
    printf("Bitte waehlen Sie Ihr Testprogramm:\n");
    printf("\t[1]: Fuehrt einen Test des Stack-Speicher aus\n");
    printf("\t[2]: Fuehrt einen Test des Queue-Speicher aus\n");
    printf("\t[3]: Fuehrt einen Test des Double-Ended Queue Speicher aus\n");
    printf("\t[4]: Fuehrt alle Tests aus (Stack, Queue und Double-Ended Queue)\n");
    printf("Ihre Auswahl: ");
    fgets(str, 255, stdin);

    switch(str[0])
    {
        case '1': runStackTest(); break;
        case '2': runQueueTest(); break;
        case '3': runDQueueTest(); break;
        case '4': runStackTest();
                  runQueueTest();
                  runDQueueTest();
                  break;
        default:
                  printf("Fehler: Eingabe ist ungueltig!\n");
                  return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

