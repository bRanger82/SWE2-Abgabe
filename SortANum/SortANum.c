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


void selectionSortArray(int numbers [], int length, bool sortAsc);
void printArrayOnStdOut(int numbers [], int length);
char *basename(char *path);

int main(int argc, char * argv[])
{
    int * values = malloc(sizeof(int) * argc - 1);
    if (NULL == values)
    {
        printf("Fehler: Speicher konnte nicht allokiert werden!\n");
        return EXIT_FAILURE;
    }
    if (argc == 1)
    {
        printf("Aufruf:\t%s N1 [N2 N3 ...]\n", basename(argv[0]));
        printf("       \tSortiert vorzeichenlose 32bit-Integer.\n");
        return EXIT_FAILURE;
    } else if (argc > 1)
    {
        for(int pos=1;pos<argc;pos++)
        {
            *(values+pos-1) = atoi(argv[pos]);
        }
        selectionSortArray(values, argc-1, true);
        printArrayOnStdOut(values, argc-1);
    }
    free(values);
    return EXIT_SUCCESS;
}

char *basename(char *path)
{
    char *s = strrchr(path, '\\');
    if (!s)
        return strdup(path);
    else
        return strdup(s + 1);
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
