/**
 * file: main.c
 *
 * Zweck: Programm-Einsprungspunkt
 *
 * date: 2017-04-25
 * progtimeest.: 120 min
 * progtimereal: 120 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TestProgram.h"

int selectAndRunTests(void); // Testauswahl und Ausfuehrung

int main()
{
    // Rueckgabewert wird einer Variablen zugewiesen, falls diese vor Return weiter verwendet werden soll
    int returnTestValue = selectAndRunTests();
    return returnTestValue;
}

/*
    Diese Methode gibt auf stdout die Auswahl der Tests aus
    und fuehrt die Tests, welche die/der Benutzer/in gewaehlt hat aus

    Rueckgabewerte:
        - EXIT_FAILURE: bei fehlerhafter Auswahl
        - EXIT_SUCCESS: Auswahl OK
*/
int selectAndRunTests(void)
{

    // Benutzer-Auswahl auf stdout ausgeben
    char str[255];
    printf("Bitte waehlen Sie Ihr Testprogramm:\n");
    printf("\t[1]: Fuehrt einen Test des Stack-Speicher aus\n");
    printf("\t[2]: Fuehrt einen Test des Queue-Speicher aus\n");
    printf("\t[3]: Fuehrt einen Test des Double-Ended Queue Speicher aus\n");
    printf("\t[4]: Fuehrt alle Tests aus (Stack, Queue und Double-Ended Queue)\n");
    printf("\t[A]: Test abbrechen\n");
    printf("Ihre Auswahl: ");

    fgets(str, 255, stdin);

    //Abhaengig davon, welche Option gewaehlt wurde den Test ausfuehren
    switch(str[0])
    {
        case 'A': return EXIT_SUCCESS;
        case '1': runStackTest(); break;
        case '2': runQueueTest(); break;
        case '3': runDeQueueTest(); break;
        case '4': runStackTest();
                  runQueueTest();
                  runDeQueueTest();
                  break;
        default:
                  printf("Fehler: Eingabe ist ungueltig!\n");
                  return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


