/**
 * file: SortFile.c
 *
 * date: 2017-03-10
 * progtimeest.: 60 min
 * progtimereal: 60 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung A.3
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 300
void selectionSortArray(int numbers [], int length, bool sortAsc);
void printArrayOnStdOut(int numbers [], int length);

void printHelp(char * path)
{
    printf("%s [Option] FILE\n", path);
    printf("Sortiert vorzeichenlose 32Bit-Integer.\n");
    printf("\n");
    printf("Option\tBeschreibung\n");
    printf("-h    \tGibt eine kurze Beschreibung der Optionen aus.\n");
    printf("-a    \tSortiert aufsteigend (default)\n");
    printf("-d    \tSortiert absteigend\n");
}

void printErrorOnStdOut(void)
{
    printf("Eingabefehler!\nBitte ueberpruefen Sie die Parameterangaben!\n");
}

int createRandomNumberFile(char * filename, bool sortAsc)
{
    FILE *fp;

    fp = fopen(filename, "r");

    if(fp == NULL)
    {
        printf("Fehler: Datei konnte nicht geoeffnet werden.\n");
        return EXIT_FAILURE;
    }

    int pos = 1;
    int * values = malloc(sizeof(int) * pos);
    char * line[MAX_LINE_SIZE];

    while (fgets(*line, MAX_LINE_SIZE, fp) != NULL)
    {
        values = realloc(values, sizeof(int) * pos);
        *(values+(pos-1)) = atoi(*line);
        pos++;
    }

    fclose(fp);

    selectionSortArray(values, pos-1, sortAsc);
    printArrayOnStdOut(values, pos-1);

    free(values);

    return EXIT_SUCCESS;
}

int main(int argc, char *argv[], char ** envp)
{
    int i = 0;
    bool sortAscending = true;
    char * filename = NULL;

    if (argc < 2)
    {
        printErrorOnStdOut();
        printHelp(argv[0]);
        return EXIT_FAILURE;
    }

    while(NULL != argv[i])
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-H") == 0)
        {
            printHelp(argv[0]);
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-D") == 0)
        {
            sortAscending = false;
        } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "-A") == 0)
        {
            sortAscending = true;
        }
        if ((argc - 1) == i)
        {
            filename = argv[i];
        }
        i++;
    }

    if (NULL == filename)
    {
        printErrorOnStdOut();
        printHelp(argv[0]);
        return EXIT_FAILURE;
    }
    createRandomNumberFile(filename, sortAscending);
    return 0;
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

