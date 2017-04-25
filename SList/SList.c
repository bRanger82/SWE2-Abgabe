/**
 * file: SList.c
 *
 * Zweck: Beinhaltet Programmcode fuer die Verwendung der Doppelt-Verketteten-Liste
 * (wird fuer DeQueue, Queue und Stack verwendet)
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
#include "SList.h"


SLIST_HEADER * createSList(void)
{
    SLIST_HEADER * p = (SLIST_HEADER *) malloc(sizeof(SLIST_HEADER));
    if (NULL == p)
    {
        return p;
    }

    p->Len = 0;
    p->First = NULL;
    p->Last = NULL;

    return p;
}

SLIST * insertFirst(SLIST_HEADER * head, void * data)
{
    SLIST * element = (SLIST *) malloc(sizeof(SLIST));
    if (NULL == element)
    {
        return element;
    }

    if (0 == head->Len)
    {
        element->Next = NULL;
        head->Last = element;
    } else
    {
        element->Next = head->First;
    }


    element->Data = data;

    head->First = element;
    head->Len++;

    return element;
}

void pr_SList(SLIST_HEADER * head)
{
    SLIST * element = head->First;
    while(NULL != element)
    {
        int * tmp = (int *) element->Data;
        printf("Data: %i\n", *tmp);
        element = element->Next;
    }
}


/**
 * Lokale OPERATIONEN, die privat gehalten werden.
 *------------------------------------------------*/

static SLIST * makeSListNode (void * userData, SLIST * aPtr)
{
   SLIST * newPtr;    /* Zeiger auf zugewiesenen Speicher */

   if ((newPtr=(SLIST *) malloc(sizeof(SLIST))) != NULL)
   {
      newPtr->Data = userData;
      newPtr->Next = aPtr;
   }
   return (newPtr);
}

/* -- Am Ende der Liste eintragen */
SLIST * insertLast(SLIST_HEADER* aList, void* userData)
{
    SLIST * newPtr;

    if ((newPtr = makeSListNode(userData, (SLIST*) NULL))!= NULL)
    {
      if (aList->Len != 0)  /* -- Liste nicht leer ? */
        aList->Last->Next= newPtr;
      else
        aList->First= newPtr;

      aList->Last= newPtr;
      aList->Len++;
    }

    return (newPtr);
}


/* -- Loeschen des ersten Listeneintrages
 * -- aList->Len muss  vorher  ueberprueft werden
 */
void * deleteFirst(SLIST_HEADER* aList)
{
   SLIST *temp;
   void  *userData;

   if (aList->Len > 0)   /* Liste nicht leer */
   {
      temp= aList->First;
      userData= temp->Data;

      aList->First= temp->Next;
      aList->Len--;

      if (aList->Len == 0) /* Wenn die Liste leer ist, Last-Zeiger auf NULL */
         aList->Last= (SLIST *) NULL;

      free( (void *) temp);         /* Knoten freigeben */
   }
   return  userData;
}


/* -- Loeschen des letzten Listeneintrages
 * -- aList->Len muss  vorher  ueberprueft werden
 */
void * deleteLast(SLIST_HEADER * aList)
{
   SLIST *temp, *help;
   void  *userData;
   int i;

   if (aList->Len > 0)   /* Liste nicht leer */
   {
      temp= aList->Last;
      userData= temp->Data;

      help= aList->First;
      aList->Last= help;
      for (i=0; i<aList->Len-1; i++){
         aList->Last= help;
         help= help->Next;
      }
      aList->Len--;

      if (aList->Len == 0) /* Wenn die Liste leer ist, Last-Zeiger auf NULL*/
      {
         aList->Last= (SLIST *) NULL;
         aList->First= (SLIST *) NULL;
      }
      free( (void *) temp);         /* Knoten freigeben */
   }
   return  userData;
}



void print_string_SList(SLIST_HEADER* aList, FILE* device)
{
    int i;
    SLIST *node;

    node= aList->First;
    for (i=1; i<=aList->Len;i++){
       fprintf(device,"%6d\t%s\n",i,(char *)node->Data);
       node= node->Next;
   }
}

void print_all_SList(SLIST_HEADER* aList, FILE* device, void (*myPrint)(FILE *, void *))
{
    int i;
    SLIST *node;

    node= aList->First;
    for (i=1; i<=aList->Len;i++){
       (*myPrint)(device,node->Data);
       node= node->Next;
   }
}


void rm_SList(SLIST_HEADER * aList)
{
    while (aList->Len)
      deleteLast(aList);

    free (aList); /* alle Knoten geloescht, Header noch freigeben */

}

void * get_entrySList(SLIST_HEADER* aList, int number)
{
    if (number>=1 && number<=aList->Len)
    {
       int i;
       SLIST *node;

       node= aList->First;
       for(i=1;i<number;i++)
         node= node->Next;
       return(node->Data);
    }
    else
       return((char *) NULL);
}
