#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "SList.h"


SLIST_HEADER * queueHead = NULL;

// Hinzufuegen eines neuen Eintrags
void * put(void * data)
{
    if (!checkQueueAvailable()) // queue initialisiert?
        queueHead = createSList();

    if (NULL == queueHead)  //konnte queue erfolgreich angelegt werden? Nein, dann return NULL
        return NULL;

    return insertLast(queueHead, data);
}

// Prueft, ob die Queue NULL oder leer (Len==0) ist (return false), sonst return true
bool checkQueueAvailable(void)
{
    if (NULL == queueHead)  //Exisitiert einen Queue
        return false;
    if (0 == queueHead->Len) //Wenn existiert, ist zumindest ein Element vorhanden?
        return false;

    return true; // Wenn Queue existiert und mindestens ein Element vorhanden gibt true zurueck
}

// Holen eines Eintrags aus dem FIFO Speicher und entfernt es
void * get(void)
{
    if (!checkQueueAvailable())  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return deleteFirst(queueHead);
}

// Abfragen des letztes hinzugefuegtem Element ohne es zu entfernen
void * last(void)
{
    if (!checkQueueAvailable())  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return get_entrySList(queueHead, queueHead->Len); //TODO
}

// Abfragen des naechsten Elements ohne es zu entfernen
void * next(void)
{
    if (!checkQueueAvailable())  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return get_entrySList(queueHead, 1); //TODO
}

// Abfragen, ob FIFO Speicher leer ist
bool Qempty(void)
{
    return !checkQueueAvailable();
}

// Abfragen, wieviele Eintrage im FIFO Speicher abgelegt sind
int Qlength(void)
{
    if (!checkQueueAvailable())  //konnte queue erfolgreich angelegt werden?
        return 0;

    return queueHead->Len;
}

// Loeschen des gesamten FIFO Speichers
void Qdelete(void)
{
    if (NULL == queueHead)  //konnte queue erfolgreich angelegt werden?
        return NULL;

    rm_SList(queueHead);
    queueHead = NULL;
}
