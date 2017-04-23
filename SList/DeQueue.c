#include <stdio.h>
#include <stdlib.h>
#include "DeQueue.h"
#include "SList.h"

const int DQ_LEN_NOT_EXIST = -1;

SLIST_HEADER * DQueueHead = NULL;

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
    if (NULL == DQueueHead)  //konnte queue erfolgreich angelegt werden?
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
    if (NULL == DQueueHead)  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return deleteFirst(DQueueHead);
}

// Abfragen des ersten Element
void * DQ_examine_first_element(void)
{
    if (DQ_empty())  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return DQueueHead->First;
}

// Abfragen des letzten Element
void * DQ_examine_last_element(void)
{
    if (DQ_empty())  //konnte queue erfolgreich angelegt werden?
        return NULL;

    return DQueueHead->Last;
}

// Abfragen, ob DEQUEUE Speicher leer ist
bool DQ_empty(void)
{
    if (NULL == DQueueHead)  //konnte queue erfolgreich angelegt werden?
        return true;

    return (0 == DQueueHead->Len);
}

// Löschen des gesamten DEQUEUE Speichers
void DQ_delete(void)
{
    if (NULL == DQueueHead)  //konnte queue erfolgreich angelegt werden?
        return false;
    rm_SList(DQueueHead);
    free(DQueueHead);
    DQueueHead = NULL;
}
