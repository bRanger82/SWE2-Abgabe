#include <stdio.h>
#include <stdlib.h>
#include "SList.h"
#include <string.h>
#include "DeQueue.h"
#include "Stack.h"
#include "Queue.h"
#include "TestProgram.h"

void readNextValueStack(void)
{
    if (NULL != (int *) top())
        printf("Stack, Lese Wert mittels pop(): %d\n", *(int *)pop());
    else
        printf("Stack, FEHLER Lese Wert: ist leer oder nicht initialisiert!\n");
}

void readLastValueDeQueue(void)
{
    if (NULL != (int *) DQ_examine_last_element())
        printf("DeQueue, Lese Wert mittels DQ_remove_element_at_back(): %d\n", *(int *)DQ_remove_element_at_back());
    else
        printf("DeQueue, FEHLER Lese Wert: ist leer oder nicht initialisiert!\n");
}

void readFirstValueDeQueue(void)
{
    if (NULL != (int *) DQ_examine_first_element())
        printf("DeQueue, Lese Wert mittels DQ_remove_element_at_front(): %d\n", *(int *)DQ_remove_element_at_front());
    else
        printf("DeQueue, FEHLER Lese Wert: ist leer oder nicht initialisiert!\n");
}

void readNextValueQueue(void)
{
    if (NULL != (int *) next())
        printf("Queue, Lese Wert mittels get(): %d\n", *(int *)get());
    else
        printf("Queue, FEHLER Lese Wert: ist leer oder nicht initialisiert!\n");
}

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
        printf("Stack: Fuege den Wert %d hinzu ... \n", i);
        push(tmp);
    }
    checkStackSize();

    readNextValueStack();
    readNextValueStack();
    readNextValueStack();
    readNextValueStack();


    printf("Stack: Sdelete() wird ausgefuehrt\n");
    Sdelete();

    checkStackSize();

    printf("********************************\n");
    printf("-----   Stack-Test Ende    -----\n");
    printf("********************************\n");
}

void checkStackSize(void)
{
    printf("checkStackSize reached\n");
    if (0 == Slength())
        printf("Test Slength(): Stack hat die Laenge 0 oder ist nicht initialisiert!\n");
    else
        printf("Test Slength(): Stack hat die Laenge %d\n", Slength());

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
    readNextValueQueue();

    int i = 0;
    for (i=0; i<5; i++)
    {
        int * tmp = (int *) malloc(sizeof(int));
        memcpy(tmp, &i, sizeof(int));
        printf("Queue: Fuege den Wert %d hinzu ... \n", i);
        put(tmp);
    }

    checkQueueSize();
    readNextValueQueue();
    readNextValueQueue();
    readNextValueQueue();
    readNextValueQueue();

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