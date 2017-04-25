/**
 * file: TestProgram.c
 *
 * Zweck: Beinhaltet das Testprogramm fuer den Stack, die Queue und die Double-Ended-Queue
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
#include "SList.h"
#include <string.h>
#include "DeQueue.h"
#include "Stack.h"
#include "Queue.h"
#include "TestProgram.h"

// Liest naechsten Wert aus dem Stack aus und gibt diese Information auf stdout aus
void readNextValueStack(void)
{
    // Bevor der Wert geholt (und damit geloescht) werden kann muss geprueft werden ob ein Wert Vorhanden ist
    // man koennte auch die Funktion Sempty() verwenden
    if (NULL != (int *) top())
        printf("\tStack, Lese Wert mittels pop(): %d\n", *(int *)pop());
    else
        printf("\tStack, FEHLER Lese Wert: ist leer oder nicht initialisiert!\n");
}

// Prueft die Antzahl der Eintrage und gibt diese Information auf stdout aus
void checkStackSize(void)
{
    // Pruefen der Laenge bzw. Anzahl der Elemente
    if (0 == Slength())
        printf("\tTest Slength(): Stack hat die Laenge 0 oder ist nicht initialisiert!\n");
    else
        printf("\tTest Slength(): Stack hat die Laenge %d\n", Slength());

    // Pruefen der Ist-Leer Funktion
    if (Sempty())
        printf("\tTest Sempty():  Stack ist leer oder nicht initialisiert!\n");
    else
        printf("\tTest Sempty():  Stack ist _nicht_ leer!\n");
}

// Testprozedur fuer den Stack
void runStackTest(void)
{
    printf("********************************\n");
    printf("-----   Stack-Test Start   -----\n");
    printf("********************************\n");

    checkStackSize();
    readNextValueStack();

    int i = 0;
    for (i=0; i<2; i++)
    {
        int * tmp = (int *) malloc(sizeof(int));
        memcpy(tmp, &i, sizeof(int));
        printf("\tStack: Fuege den Wert %d hinzu ... \n", i);
        push(tmp);
    }
    checkStackSize();

    readNextValueStack();
    readNextValueStack();
    readNextValueStack();
    readNextValueStack();


    printf("\tStack: Sdelete() wird ausgefuehrt\n");
    Sdelete();

    checkStackSize();

    printf("********************************\n");
    printf("-----   Stack-Test Ende    -----\n");
    printf("********************************\n");
}

// Liest naechsten Wert aus der Queue aus und gibt diese Information auf stdout aus
void readNextValueQueue(void)
{
    if (NULL != (int *) next())
        printf("\tQueue, Lese Wert mittels get(): %d\n", *(int *)get());
    else
        printf("\tQueue, FEHLER Lese Wert: ist leer oder nicht initialisiert!\n");
}

// Prueft die Antzahl der Eintrage und gibt diese Information auf stdout aus
void checkQueueSize(void)
{
    // Pruefen der Laenge bzw. Anzahl der Elemente
    if (0 == Qlength())
        printf("\tTest Qlength(): Queue hat die Laenge 0 oder ist nicht initialisiert!\n");
    else
        printf("\tTest Qlength(): Queue hat die Laenge %d\n", Qlength());

    // Pruefen der Ist-Leer Funktion
    if (Qempty())
        printf("\tTest Qempty():  Queue ist leer oder nicht initialisiert!\n");
    else
        printf("\tTest Qempty():  Queue ist _nicht_ leer!\n");
}

// Testprozedur fuer die Queue
void runQueueTest(void)
{
    printf("********************************\n");
    printf("-----   Queue-Test Start   -----\n");
    printf("********************************\n");

    checkQueueSize();
    readNextValueQueue();

    //Elemente hinzfuegen, Speicher muss zuvor mittels malloc allokiert werden
    int i = 0;
    for (i=0; i<5; i++)
    {
        int * tmp = (int *) malloc(sizeof(int));
        memcpy(tmp, &i, sizeof(int));
        printf("\tQueue: Fuege den Wert %d hinzu ... \n", i);
        put(tmp);
    }

    checkQueueSize();
    readNextValueQueue();
    readNextValueQueue();
    readNextValueQueue();
    readNextValueQueue();

    checkQueueSize();

    printf("\tQueue: Qdelete() wird ausgefuehrt\n");
    Qdelete();

    checkQueueSize();
    printf("********************************\n");
    printf("-----   Queue-Test Ende    -----\n");
    printf("********************************\n");
}

// Prueft die Antzahl der Eintrage und gibt diese Information auf stdout aus
void checkDeQueueSize(void)
{
    // Pruefen der Laenge bzw. Anzahl der Elemente
    if (0 == DQ_length())
        printf("\tTest DeQlength(): DeQueue hat die Laenge 0 oder ist nicht initialisiert!\n");
    else
        printf("\tTest DeQlength(): DeQueue hat die Laenge %d\n", DQ_length());

    // Pruefen der Ist-Leer Funktion
    if (DQ_empty())
        printf("\tTest DQ_empty():  DeQueue ist leer oder nicht initialisiert!\n");
    else
        printf("\tTest DQ_empty():  DeQueue ist _nicht_ leer!\n");
}

// Liest den _hinteren_ Wert aus der Double-Ended-Queue aus und gibt diese Information auf stdout aus
void readLastValueDeQueue(void)
{
    if (NULL != (int *) DQ_examine_last_element())
        printf("\tDeQueue, Lese Wert mittels DQ_remove_element_at_back(): %d\n", *(int *)DQ_remove_element_at_back());
    else
        printf("\tDeQueue, FEHLER Lese Wert: ist leer oder nicht initialisiert!\n");
}

// Liest den _vorderen_ Wert aus der Double-Ended-Queue aus und gibt diese Information auf stdout aus
void readFirstValueDeQueue(void)
{
    if (NULL != (int *) DQ_examine_first_element())
        printf("\tDeQueue, Lese Wert mittels DQ_remove_element_at_front(): %d\n", *(int *)DQ_remove_element_at_front());
    else
        printf("\tDeQueue, FEHLER Lese Wert: ist leer oder nicht initialisiert!\n");
}

// Testprozedur fuer die Double-Ended-Queue
void runDeQueueTest(void)
{
    printf("********************************\n");
    printf("-----  DeQueue-Test Start  -----\n");
    printf("********************************\n");

    checkDeQueueSize();

    int i = 0; // For-Schleife, Hinzufuegen der Elemente

    //Elemente hinzfuegen, Speicher muss zuvor mittels malloc allokiert werden
    for (i=0; i<2; i++)
    {
        int * tmp = (int *) malloc(sizeof(int));
        memcpy(tmp, &i, sizeof(int));
        printf("\tDeQueue: Fuege den Wert %d hinzu (DQ_insert_element_at_front) \n", i);
        DQ_insert_element_at_front(tmp);
    }

    for (i=5; i>3; i--)
    {
        int * tmp = (int *) malloc(sizeof(int));
        memcpy(tmp, &i, sizeof(int));
        printf("\tDeQueue: Fuege den Wert %d hinzu (DQ_insert_element_at_last) \n", i);
        DQ_insert_element_at_back(tmp);
    }

    checkDeQueueSize();

    readFirstValueDeQueue();
    readLastValueDeQueue();
    readFirstValueDeQueue();
    readLastValueDeQueue();


    printf("\tDeQueue: DQ_delete() wird ausgefuehrt\n");
    DQ_delete();

    checkDeQueueSize();

    printf("********************************\n");
    printf("-----  DeQueue-Test Ende   -----\n");
    printf("********************************\n");
}



