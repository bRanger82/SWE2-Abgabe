#include <stdio.h>
#include <stdlib.h>
#include "DeQueue.h"
#include "SList.h"


SLIST_HEADER * DQueueHead = NULL;


// Prueft, ob die DeQueue NULL oder leer (Len==0) ist (return false), sonst return true
bool checkDeQueueAvailable(void)
{
    if (NULL == DQueueHead)  //konnte queue erfolgreich angelegt werden?
        return false;

    if (0 == DQueueHead->Len)
        return false;

    return true;
}

// Hinzufügen eines neuen Eintrags in den DEQUEUE Speicher
void * DQ_insert_element_at_back(void * data)
{
    if (NULL == DQueueHead) // queue initialisiert?
        DQueueHead = createSList();

    if (NULL == DQueueHead)  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return insertLast(DQueueHead, data);
}

// Holen eines Eintrags aus dem DEQUEUE Speicher
void * DQ_remove_element_at_back(void)
{
    if (!checkDeQueueAvailable())  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return deleteLast(DQueueHead);
}

// Hinzufügen eines neuen Eintrags in den DEQUEUE Speicher
void * DQ_insert_element_at_front(void * data)
{
    if (NULL == DQueueHead) // queue initialisiert?
        DQueueHead = createSList();

    if (NULL == DQueueHead)  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return insertFirst(DQueueHead, data);
}

// Holen eines Eintrags aus dem DEQUEUE Speicher
void * DQ_remove_element_at_front(void)
{
    if (!checkDeQueueAvailable())  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return deleteFirst(DQueueHead);
}

// Abfragen des ersten Element
void * DQ_examine_first_element(void)
{
    if (!checkDeQueueAvailable())  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return DQueueHead->First;
}

// Abfragen des letzten Element
void * DQ_examine_last_element(void)
{
    if (!checkDeQueueAvailable())  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return DQueueHead->Last;
}

// Abfragen, ob DEQUEUE Speicher leer ist
bool DQ_empty(void)
{
    return !checkDeQueueAvailable();
}

// Löschen des gesamten DEQUEUE Speichers
void DQ_delete(void)
{
    if (NULL == DQueueHead)  //Keine DeQueue vorhanden
        return;

    rm_SList(DQueueHead);
    DQueueHead = NULL;
}
