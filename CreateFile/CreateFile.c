/**
 * file: CreateFile.c
 *
 * date: 2017-03-10
 * progtimeest.: 60 min
 * progtimereal: 60 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung A.2
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

const int defaultCountNumbers = 100;
const int defaultNumberRange = 100;

void printHelp(char * path)
{
    printf("Das Programm erzeugt eine Datei mit Zufallszahlen.\n");
    printf("Aufruf: %s [-h] [-r <zahl>] [-n <zahl>] Dateiname\n", path);
    printf("Bedeutung der Parameter:\n");
    printf("\t-n [Anzahl der Zahlen] (Muss groesser 0 sein, Standard: 100), Beispiel: -r 50 (50 Zahlen werden geschrieben)\n");
    printf("\t-r [Zahlenbereich] (Muss groesser 0 sein, Standard: 100), Beispiel: -n 200 (Zahlen von 0 bis 200)\n");
    printf("\t-h Gibt diese Hilfe aus\n");
    printf("\tDateiname: Name der Datei, in welche die Daten geschrieben werden\n");
    printf("\tACHTUNG: Dateiname muss als letzter Parameter gesetzt sein\n");
}

int createRandomNumberFile(char * filename, int countNumbers, int numberRange, bool initRandomizer, bool writeBinary)
{
    FILE *fp;

    fp = fopen(filename, "w");

    if(fp == NULL)
    {
        printf("Fehler: Datei konnte nicht geoeffnet werden.\n");
        return EXIT_FAILURE;
    }

    if (initRandomizer)
        srand((unsigned)time(NULL));

    int i;
    for(i=1; i<=countNumbers; i++)
    {
        int randNum = rand() % numberRange;

        if (writeBinary)
            fwrite(&randNum, sizeof(int), 1, fp);
        else
            fprintf(fp, "%i\n", randNum);
    }
    fclose(fp);

    return EXIT_SUCCESS;
}

void printErrorOnStdOut(void)
{
    printf("Eingabefehler!\nBitte ueberpruefen Sie die Parameterangaben!\n");
}

int main(int argc, char *argv[], char ** envp) {
    int i = 0;
    int countNumbers = defaultCountNumbers;
    int numberRange = defaultNumberRange;
    bool errorEingabe = false;
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
        } else if (strcmp(argv[i], "-n") == 0 || strcmp(argv[i], "-N") == 0)
        {
            if (argc > i)
                if (atoi(argv[i+1]) > 0)
                {
                    countNumbers = atoi(argv[i+1]);
                    i += 2;
                    continue;
                }
                else
                    errorEingabe = true;
            else
                errorEingabe = true;
        } else if (strcmp(argv[i], "-r") == 0 || strcmp(argv[i], "-R") == 0)
        {
            if (argc > i)
                if (atoi(argv[i+1]) > 0)
                {
                    numberRange = atoi(argv[i+1]);
                    i += 2;
                    continue;
                }
                else
                    errorEingabe = true;
            else
                errorEingabe = true;
        }
        if ((argc - 1) == i)
        {
            filename = argv[i];
        }
        if (errorEingabe)
        {
            printErrorOnStdOut();
            printHelp(argv[0]);
            return EXIT_FAILURE;
        }
        i++;
    }
    if (NULL == filename)
    {
        printErrorOnStdOut();
        printHelp(argv[0]);
        return EXIT_FAILURE;
    }

    return createRandomNumberFile(filename, countNumbers, numberRange, true, false);
}
