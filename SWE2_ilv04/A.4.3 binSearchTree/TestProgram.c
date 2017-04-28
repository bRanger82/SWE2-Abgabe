/**
 * file: TestProgram.c
 *
 * Zweck: Implementierung fuer das Testprogramm fuer den binaeren Suchbaum
 *
 * date: 2017-04-28
 * progtimeest.: 120 min
 * progtimereal: 120 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung 4/2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "TestProgram.h"

/*
    Gibt eine Zufallszahl im Bereich zwischen 1 und max zurueck
    Parameter:
        max: Maximaler Wert der Zufallszahl
        initRand: bei Aufruf [false] gleiche Zufallszahlen, [true] rand() unterschiedliche Zufallszahlen
    Rueckgabewert:
        Zufallszahl zwischen 1 und max
*/
int getRandNum(int max, bool initRand)
{
    if (initRand)
        srand(time(NULL));

    return (rand() % max) + 1;
}

/*
    Fuegt eine Anzahl von Werten in den binaeren Suchbaum ein
    Parameter:
        cnt: Anzahl von Werten die eingefuegt werden sollen
        initRand: Zufallszahlen immer gleich [false] oder unterschiedlich [true]
        maxValue: Obergrenze fuer den Zahlenbereich, welcher eingefuegt werden soll
    Rueckgabewert:
        Adresse auf den binaeren Suchbaum
*/
KNOTEN * createTestValues(int cnt, bool initRand, int maxValue)
{
    int pos;
    KNOTEN * wurzel = NULL;

    for (pos=0; pos < cnt; pos++)
    {
        wurzel=einordnen(wurzel, getRandNum(maxValue, initRand));
        if (NULL == wurzel)
            return NULL;

    }
    return wurzel;
}

/*
    Fuehrt die Travesieren-Methoden aus und gibt die Information auf stdout aus
    Parameter:
        root: binaere Suchbaum
*/
void printOrder(KNOTEN * root)
{
    if (NULL == root)
        return;

    printf("\nInorder   (LVR)\n");
    inorder_print(root);
    printf("\nPostorder (LRV)\n");
    postorder_print(root);
    printf("\nPreorder  (VLR)\n");
    preorder_print(root);
}

/*
    Sucht einen Wert in einem binaeren Suchbaum
    Parameter:
        - root: binaere Suchbaum, in dem gesucht werden soll
        - searchValue: der Wert, nach dem gesucht werden soll
    Rueckgabewert:
        - Wenn Wert gefunden dann Adresse auf das binaere Blatt, sonst NULL
*/
KNOTEN * searchValue(KNOTEN * root, int seachValue)
{
    if (NULL == root)
        return NULL;

    printf("\nSuche nach Wert %d ...\n", seachValue);

    KNOTEN * find = suchen(root, seachValue);
    if (NULL == find)
        printf("\tWert '%d' konnte nicht gefunden.\n", seachValue);
    else
        printf("\tWert '%d' gefunden!\n", seachValue);

    return find;
}

/*
    Liest einen integer Wert von stdin aus
    Rueckgabewert:
        - eingegebener Integer Wert
*/
int getNumberFromStdIn(void)
{
    int readInVal;
    int result = scanf("%d", &readInVal);

    if (result == EOF) {
        return 0;
    }
    if (result == 0) {
        while (fgetc(stdin) != '\n') // Read until a newline is found
            ;
    }
    return readInVal;
}
