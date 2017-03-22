/**
 * file: SortANum.c
 *
 * date: 2017-03-10
 * progtimeest.: 60 min
 * progtimereal: 60 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung A.1
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

void selSortOne(void * base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
int compare(const void *a, const void *b);

void selectionSortArray(int numbers [], int length, bool sortAsc); //Sortiert Array Methode (Selection-Sort)
void printArrayOnStdOut(int numbers [], int length); //Ausgabe Array auf stdout

int main(int argc, char * argv[])
{
    //Speicherbereich fuer Array reservieren
    int * values = malloc(sizeof(int) * argc - 1);
    // Speicher konnte nicht reserviert werden
    if (NULL == values)
    {
        printf("Fehler: Speicher konnte nicht allokiert werden!\n");
        return EXIT_FAILURE;
    }
    //Anzahl der Parameter ist 1 -> es wurden keine Werte angegeben -> Hilfe anzeigen
    if (argc == 1)
    {
        printf("Aufruf:\t%s N1 [N2 N3 ...]\n", argv[0]);
        printf("       \tSortiert vorzeichenlose 32bit-Integer.\n");
        free(values);
        return EXIT_FAILURE;
    } else if (argc > 1)
    {
        //Werte der Parameter in Array ablegen
        int pos;
        for(pos=1;pos<argc;pos++)
        {
            *(values+pos-1) = atoi(argv[pos]);
        }
        //Array sortieren
        //selectionSortArray(values, argc-1, true);
        qsort(values, argc-1, sizeof(int), compare);
        //Array auf stdout ausgeben
        printArrayOnStdOut(values, argc-1);
    }
    //Speicherbereich wieder freigegeben
    free(values);
    return EXIT_SUCCESS;
}

void selSortOne(void * base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    size_t pos;
    for(pos=0;pos<nmemb;pos++)
    {
        //printf("%d\n", *(base+pos));
    }
}

int compare(const void *a, const void *b)
{
  return (* (int *) a - * (int *) b);
}


/*
    Sortiert einen Array entweder aufsteigend (sortAsc = true) oder absteigend (sortAsc = false)
*/
void selectionSortArray(int numbers [], int length, bool sortAsc)
{
    int i, o, notSortedIndex;

    for(o=0;o<(length-1);o++)
    {
        notSortedIndex = o;
        for(i=o+1;i<length;i++)
        {
            if (sortAsc ? (numbers[notSortedIndex] > numbers[i]) : (numbers[notSortedIndex] < numbers[i]))
            {
                notSortedIndex = i;
            }
        }
        if (notSortedIndex != o)
        {
            int help = numbers[notSortedIndex];
            numbers[notSortedIndex] = numbers[o];
            numbers[o] = help;
        }
    }
}

// Ausgabe jedes Elements im Array numbers auf stdout
void printArrayOnStdOut(int numbers [], int length)
{
    int pos;

    for (pos=0;pos<length;pos++)
        printf("%d ", numbers[pos]);

    printf("\n");
}
