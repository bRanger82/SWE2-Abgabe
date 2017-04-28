/**
 * file: main.c
 *
 * Zweck: Ausfuehrendes Programm
 *
 * date: 2017-04-28
 * progtimeest.: 120 min
 * progtimereal: 120 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung A.4.3
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "TestProgram.h"

#define CNT_MIN 2   // Minimum Anzahl Eintraege binaerer Suchbaum
#define CNT_MAX 50  // Maximum Anzahl Eintraege binaerer Suchbaum
#define VAL_MIN 4   // Minimum fuer den oberen Zahlenbereich der Werte fuer den binaeren Suchbaum
#define VAL_MAX 50  // Minimum fuer den oberen Zahlenbereich der Werte fuer den binaeren SuchbaumMaximum

int main(void)
{
    // Hier soll die Anzahl der Eintraege fuer den binaeren Suchbaum angegeben werden
    printf("Bitte Anzahl der Testwerte eingeben: (zwischen %d und %d)\n", CNT_MIN, CNT_MAX);
    int cnt = getNumberFromStdIn();
    if (cnt < CNT_MIN || cnt > CNT_MAX)
    {
        printf("Fehler: Zahl liegt nicht zwischen %d und %d!\n", CNT_MIN, CNT_MAX);
        return EXIT_FAILURE;
    }

    // Hier soll der obere Zahlenbereich definiert werden
    printf("Bitte Bereich der Testwerte eingeben von 1 bis zwischen %d und %d\n", VAL_MIN, VAL_MAX);
    int valueRange = getNumberFromStdIn();
    if (valueRange < VAL_MIN || valueRange > VAL_MAX)
    {
        printf("Fehler: Zahl liegt nicht zwischen %d und %d!\n", VAL_MIN, VAL_MAX);
        return EXIT_FAILURE;
    }

    // Knoten mit Testwerten erstellen mit [cnt] Blaetter und einem Zahlenbereich zwischen 1 und valueRange
    KNOTEN * wurzel = createTestValues(cnt, false, valueRange);
    if (NULL == wurzel)
    {
        printf("Fehler: Baum konnte nicht erstellt werden\n");
        return EXIT_FAILURE;
    }

    // Ausgabe der Travesieren-Methoden auf stdout
    printOrder(wurzel);

    // mehrere Suchversuche zulassen
    while(true)
    {
        printf("\nBitte geben Sie die Zahl ein nach der Sie suchen wollen (zwischen 1 und %d)\nEingabe von 0 beendet das Programm:\n", valueRange);
        int searchVal = getNumberFromStdIn();
        if (searchVal == 0)
            break;
        else if (searchVal >= 1 && searchVal <= valueRange)
            searchValue(wurzel, searchVal);
        else
            printf("Fehler: ungueltige Eingabe!\n");
    }

    freeTree(wurzel);

    return EXIT_SUCCESS;
}
