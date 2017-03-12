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

const int defaultCountNumbers = 100; // Standard-Anzahl Ausgabe Nummern
const int defaultNumberRange = 100;  // Standard-Zahlenbereich (0 bis 100)
void printHelp(char * path); //Ausgabe der Hilfe bzw. Verwendung auf stdout
int createRandomNumberFile(char * filename, int countNumbers, int numberRange, bool initRandomizer, bool writeBinary); //Methode erstellt Ausgabedatei
void printErrorOnStdOut(void);// Ausgabe der Fehlermeldung auf stdout bei Fehlerhaften Parametern

int main(int argc, char *argv[], char ** envp)
{
    int i = 0; //Fuer das Durchlaufen der Parameter (argv)
    int countNumbers = defaultCountNumbers; //Anzahl der Zufallszahlen
    int numberRange = defaultNumberRange; //Bereich der Zufallszahlen
    bool errorEingabe = false; //Pruefvariable ob Fehler bei Parameter-Eingabe
    char * filename = NULL; // Dateiname fuer die Ausgabedatei

    //Erwartete Anzahl Parameter muss mindestens 2 sein
    if (argc < 2)
    {
        printErrorOnStdOut();
        printHelp(argv[0]);
        return EXIT_FAILURE;
    }

    //Lese Parameter und pruefe, welche Werte gesetzt wurden
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
            // argv[x] argv[x+1] ...
            // -r      2
            // Wenn Parameter argv[x] -r gesetzt hat
            // ist  Parameter argv[x+1] der zugehoerige Wert zu Parameter -r
            // daraufhin kann der naechste Wert fuer 'i' (x+1) uebersprungen werden
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
        //Dateiname muss als letzter Parameter-Wert gesetzt sein
        if ((argc - 1) == i)
        {
            filename = argv[i];
        }
        //Bei fehlerhafter Parameter-Eingabe Ausgabe der Fehlermeldung auf stdout und Abbruch
        if (errorEingabe)
        {
            printErrorOnStdOut();
            printHelp(argv[0]);
            return EXIT_FAILURE;
        }
        i++;
    }

    //Pruefung, ob Dateiname gesetzt wurde. Wenn nicht Fehlermeldung anzeigen und Programm abbrechen
    if (NULL == filename)
    {
        printErrorOnStdOut();
        printHelp(argv[0]);
        return EXIT_FAILURE;
    }

    //Datei erstellen (wenn createRandomNumberFile nicht erfolgreich wird EXIT_FAILURE zurueck gegeben, sonst EXIT_SUCCESSFUL)
    return createRandomNumberFile(filename, countNumbers, numberRange, true, false);
}

/*
    Ausgabe der Hilfe bzw. Verwendung auf stdout
*/
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

/*
    Erstellt eine Datei mit Zufallszahlen
    Parameter:
        - [filename]: Dateiname fuer die Datei, in welche die Werte gespeichert werden
        - [countNumbers]: Anzahl von Zufallszahlen, welche in die Datei geschrieben werden
        - [numberRange]: Zahlenbereich fuer die Zufallszahlen (von 0 bis numberRange)
        - [initRandomizer]: TRUE fuehrt zu einem Initialisieren der Zufallszahl, FALSE liefert fuer jeden Aufruf die selben Zahlen
        - [writeBinary]: TRUE bedeutet, dass die Ausgabedatei als Binaerdatei gespeichert wird. Bei FALSE erfolgt die Speicherung als plain-text
    Rueckgabewerte:
        - EXIT_SUCCESS: Die Methode wurde erfolgreich ausgefuehrt
        - EXIT_FAILURE: Die Methode wurde nicht erfolgreich ausgefuehrt. Fehlermeldungen erfolgen ueber printf()
*/
int createRandomNumberFile(char * filename, int countNumbers, int numberRange, bool initRandomizer, bool writeBinary)
{

    if (countNumbers < 1)
    {
        printf("Fehler: es wurden weniger als 1 Zahl angegeben!\n");
        return EXIT_FAILURE;
    }

    if (numberRange < 1)
    {
        printf("Fehler: der Zahlenbereich ist kleiner als 1!\n");
        return EXIT_FAILURE;
    }

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

// Ausgabe der Fehlermeldung auf stdout bei Fehlerhaften Parametern
void printErrorOnStdOut(void)
{
    printf("Eingabefehler!\nBitte ueberpruefen Sie die Parameterangaben!\n");
}

//Programm Ende
