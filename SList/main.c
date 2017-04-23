#include <stdio.h>
#include <stdlib.h>
#include "SList.h"
#include <string.h>
#include "DeQueue.h"
#include "Stack.h"
#include "Queue.h"

void runStackTest(void);
void runQueueTest(void);
void runDQueueTest(void);
int selectAndRunTests(void);
void checkQueueSize(void);
void checkStackSize(void);

int main()
{
    return selectAndRunTests();
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

void runStackTest(void)
{
    printf("********************************\n");
    printf("-----   Stack-Test Start   -----\n");
    printf("********************************\n");

    checkStackSize();
    int i = 0;
    for (i=0; i<5; i++)
    {
        int * tmp = (int *) malloc(sizeof(int));
        memcpy(tmp, &i, sizeof(int));
        printf("Stack: Fuege den Wert %d hinzu ... \n", i);
        push(tmp);
    }
    checkStackSize();
    printf("Stack, Lese Wert mittels get(): %d\n", *(int *)pop());
    printf("Stack, Lese Wert mittels get(): %d\n", *(int *)pop());
    printf("Stack, Lese Wert mittels get(): %d\n", *(int *)pop());
    printf("Stack, Lese Wert mittels get(): %d\n", *(int *)pop());

    printf("Stack: Sdelete() wird ausgefuehrt\n");
    Sdelete();

    checkStackSize();

    printf("********************************\n");
    printf("-----   Stack-Test Ende    -----\n");
    printf("********************************\n");
}

void checkStackSize(void)
{
    if (0 == Slength())
        printf("Test Slength(): Stack hat die Laenge 0 oder ist nicht initialisiert!\n");
    else
        printf("Test Slength(): Stack hat die Laenge %d\n", Qlength());

    if (Sempty())
        printf("Test Sempty():  Stack ist leer oder nicht initialisiert!\n");
    else
        printf("Test Sempty():  Stack ist _nicht_ leer!\n");
}

void checkQueueSize(void)
{
    if (0 == Qlength())
        printf("Test Qlength(): Queue hat die Laenge 0 oder ist nicht initialisiert!\n");
    else
        printf("Test Qlength(): Queue hat die Laenge %d\n", Qlength());

    if (Qempty())
        printf("Test Qempty():  Queue ist leer oder nicht initialisiert!\n");
    else
        printf("Test Qempty():  Queue ist _nicht_ leer!\n");
}

void runQueueTest(void)
{
    printf("********************************\n");
    printf("-----   Queue-Test Start   -----\n");
    printf("********************************\n");

    checkQueueSize();

    int i = 0;
    for (i=0; i<5; i++)
    {
        int * tmp = (int *) malloc(sizeof(int));
        memcpy(tmp, &i, sizeof(int));
        printf("Queue: Fuege den Wert %d hinzu ... \n", i);
        put(tmp);
    }

    checkQueueSize();

    printf("Queue, Lese Wert mittels get(): %d\n", *(int *)get());
    printf("Queue, Lese Wert mittels get(): %d\n", *(int *)get());
    printf("Queue, Lese Wert mittels get(): %d\n", *(int *)get());
    printf("Queue, Lese Wert mittels get(): %d\n", *(int *)get());


    checkQueueSize();

    printf("Queue: Qdelete() wird ausgefuehrt\n");
    Qdelete();

    checkQueueSize();
    printf("********************************\n");
    printf("-----   Queue-Test Ende    -----\n");
    printf("********************************\n");
}

void runDQueueTest(void)
{
    printf("********************************\n");
    printf("--  Double-Ended-Queue Start  --\n");
    printf("********************************\n");

    if (DQ_empty())
        printf("Double-Ended-Queue ist leer oder nicht initialisiert!\n");


    printf("********************************\n");
    printf("--  Double-Ended-Queue Ende   --\n");
    printf("********************************\n");
}
