/**
 * file: Stack.c
 *
 * Zweck: Beinhaltet Programmcode fuer den Stack
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
#include <stdbool.h>
#include "Stack.h"
#include "SList.h"


SLIST_HEADER * stackHead = NULL;

/* Prueft, ob der Stack angelegt und zumindest ein Datensatz vorhanden ist
   Return-Werte:
        - true: stack nicht NULL und Len > 0
        - sonst false
*/
bool checkStackAvailable(void)
{
    if (NULL == stackHead)  //Exisitiert einen Queue
        return false;
    if (0 == stackHead->Len) //Wenn existiert, ist zumindest ein Element vorhanden?
        return false;

    return true; // Wenn Queue existiert und mindestens ein Element vorhanden gibt true zurueck
}

/*
    Element der obersten Stack Position, ohne es aus dem Stack zu entfernen
    Return Werte
        Stack leer: ERROR_STACK
        Stack nicht leer: oberstes Element Stack
*/
void * top()
{
    if (!checkStackAvailable())
        return NULL;

    SLIST * element = stackHead->Last;
    return element->Data;
}


/*
    Pruefung ob Stack leer ist
    Return Werte
        True wenn Stack leer
        False wenn Stack nicht leer
*/
bool Sempty()
{
    return !checkStackAvailable(); // TODO
}

/*
    Fuegt ein neues Element dem Stack hinzu
    Parameter:
        value ... Wert, dem der Stack hinzugefuegt werden soll
    Return Werte
        ERROR_STACK wenn Stack voll ist
        Das Element wenn erfolgreich
*/
void * push(void * data)
{
    if (NULL == stackHead) //stack bereits erstellt?
        stackHead = createSList();
    if (NULL == stackHead) //konnte stack erfolgreich angelegt werden?
        return NULL;
    return insertLast(stackHead, data);
}

/*
    Liest das oberste Element aus dem Stack aus und entfernt es aus diesem
    Return Werte:
        ERROR_STACK wenn Stack leer ist
        Das gelesene Element
*/
void * pop()
{
    if (!checkStackAvailable())
        return NULL;

    return deleteLast(stackHead);
}

//Gibt die Anzahl der Elemente im Stack zurueck
int Slength(void)
{
    if (!checkStackAvailable())
        return 0;

    return stackHead->Len; //TODO
}

//Setzt den Stack zurueck und loescht auch den Inhalt
void Sdelete(void)
{
    if (NULL == stackHead)  //Exisitiert einen Queue
        return;

    rm_SList(stackHead);
    stackHead = NULL;
}


