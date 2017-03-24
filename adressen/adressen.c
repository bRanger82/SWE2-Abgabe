/**
 * file: adressen.c
 *
 * date: 2017-03-24
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
#include <string.h>
#include <stdbool.h>

struct datum
{
    int tag;
    int monat;
    int jahr;
    char mon_name[4];
}; typedef struct datum TDATUM;

#define LEN 20
struct adres
{
    char vname[LEN];
    char nname[LEN];
    long PLZ;
    char ort[LEN];
    TDATUM geburtsjahr;
}; typedef struct adres TADRESS;


void help(void); // Gibt einen Hilfetext auf stdout aus
TDATUM mache_date(int t, int m, int j); // Erstellt ein TDATUM Objekt anhand der uebergebenen Werte
TADRESS * einlesen(char * filename, int * anzahl); // Liest Daten aus einer Datei ein
void ZeigeDatenAn(TADRESS * ta, int anzahl);  // Ausgbae der Adressdaten auf stdout
void ausgabe(TADRESS* p, int anzahl, char * filename); // Ausgbae der Adressdaten in eine Datei
void ausgabe_html(TADRESS* p, int anzahl, char * filename); // Erstellt eine HTML Datei mit den Adressdaten
void sort_name(TADRESS* p, int anzahl); // Sortiert alle Adressen nach Namen
void suche_name(TADRESS* p, int anzahl, char *name); // Sortiert alle Adressen nach Namen und durchse diese
int compareName(const void *nameOne, const void *nameTwo); // Funktion fuer den Vergleich der Namen

char * executableFileName; //Speichert den Pfad inklusive Dateinamen dieses Programms

//Hilfs-Array fuer das Setzten des Monatsnamen
const char * monat[12] = {"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dez"};

/*
    Gibt einen Teil-String eines String zurueck
    Parameter:
        inputString: Eingabeparameter, kompletter String
        subString: Ausgabeparameter, enthaelt den Teil-String
        index: Eingabeparameter, definiert die Start-Position von der der inputString ausgelesen werden soll
        subStringLength: Eingabeparameter, definiert die Laenge des inputString von Position index weg
    Rueckgabewert:
        subString
*/
char* getSubString(const char* inputString, char* subString, int index, int subStringLength)
{
    int counter, inputStringLength = strlen(inputString);

    //Pruefung der Laengen bzw. Positionen
    if(index < 0 || index > inputStringLength ||
          (index + subStringLength) > inputStringLength){
        printf("Fehler: Teil-String konnte nicht verarbeitet werden!");
        return NULL;
    }

    for(counter = 0; counter < subStringLength; counter++){
        subString[counter] = inputString[index++];
    }

    subString[counter] = '\0';

    return subString;
}

int main(int argc, char * argv[])
{

    executableFileName = argv[0];

    int i = 0;
    char * filename = NULL;
    char * htmlFilename = NULL;
    char * suchMuster = NULL;
    bool showAllAdresses = false;
    bool sortAdresses = false;
    bool errorCommandline = false;
    //Parameter einlesen
    while(NULL != argv[i])
    {
        if (strcmp(argv[i], "-h") == 0)
        {
            help();
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-p") == 0)
        {
            showAllAdresses = true;
        } else if (strcmp(argv[i], "-s") == 0)
        {
            sortAdresses = true;
            showAllAdresses = true;
        } else if ((argc - 1) == i)
        {
            filename = argv[i];
        } else if (strcmp(argv[i], "-w") == 0)
        {
            if (argc < (i+1))
            {
                errorCommandline = true;
                break;
            }
            htmlFilename = argv[++i];
        } else if (strcmp(argv[i], "-f") == 0)
        {
            if (argc < (i+1))
            {
                errorCommandline = true;
                break;
            }
            suchMuster = argv[++i];
        }
        i++;
    }

    if (errorCommandline || argc < 2)
    {
         printf("Fehler: die Parameter konnten nicht verarbeitet werden.\n");
         printf("        Bitte rufen Sie das Programm mit dem Parameter -h auf\n");
         printf("        um eine Auflistung aller moeglichen Parameter zu erhalten.\n");
         return EXIT_FAILURE;
    }

    //Pruefung ob Dateiname als Parameter gesetzt wurde
    if (NULL == filename)
    {
        printf("Fehler: Es wurde kein Dateiname angegeben!\n\n");
        return EXIT_FAILURE;
    }

    int anzahlDatensaetze = 0;
    TADRESS * adressen = einlesen(filename, &anzahlDatensaetze);

    if (NULL == adressen)
    {
        printf("Ein Fehler ist aufgetreten!\n\n");
        return EXIT_FAILURE;
    }

    if (sortAdresses)
    {
        sort_name(adressen, anzahlDatensaetze);
    }

    if (showAllAdresses)
    {
        ZeigeDatenAn(adressen, anzahlDatensaetze);
    }

    if (NULL != htmlFilename)
    {
        ausgabe_html(adressen, anzahlDatensaetze, htmlFilename);
    }

    if (NULL != suchMuster)
    {
        suche_name(adressen, anzahlDatensaetze, suchMuster);
    }

    //Speicher wieder freigeben
    free(adressen);

    return EXIT_SUCCESS;
}

void suche_name(TADRESS* p, int anzahl, char *name)
{
    sort_name(p, anzahl);
    TADRESS * foundItems = NULL;
    foundItems = (TADRESS*) bsearch(name, p, anzahl, sizeof(TADRESS), compareName);
    if (NULL == foundItems)
    {
        printf("Es konnte kein Eintrag zu dem Namen '%s' gefunden werden\n", name);
        return;
    } else
    {
        ZeigeDatenAn(foundItems, 1);
    }
}

void ausgabe_html(TADRESS* p, int anzahl, char * filename)
{
    FILE * fp = fopen(filename, "w");
    if (NULL == fp)
    {
        printf("Fehler: HTML Datei konnte nicht gespeichert werden!\n");
        return;
    }

    fprintf(fp, "<html>\n");
    fprintf(fp, "<head>\n");
    fprintf(fp, "Ausgabe der Adressen in HTML Form</br>\n");
    fprintf(fp, "</head>\n");
    fprintf(fp, "<body>\n");
    int pos;
    for (pos=0;pos<anzahl;pos++)
    {
        fprintf(fp, "Datensatz %d</br>\n", pos+1);
        fprintf(fp, "&emsp; Vorname:      %s</br>\n", (p+pos)->vname);
        fprintf(fp, "&emsp; Nachname:     %s</br>\n", (p+pos)->nname);
        fprintf(fp, "&emsp; PLZ:          %ld</br>\n",(p+pos)->PLZ);
        fprintf(fp, "&emsp; Ort:          %s</br>\n", (p+pos)->ort);
        TDATUM u = (p+pos)->geburtsjahr;
        fprintf(fp, "&emsp; Geburtsdatum: %d.%d.%d</br>\n", u.tag, u.monat, u.jahr);
        fprintf(fp, "&emsp; Geburtsmonat: %s</br>\n", u.mon_name);
        fprintf(fp, "</br>");
    }
    fprintf(fp, "</body>\n");
    fprintf(fp, "</html>\n");
    fclose(fp);
}

void ZeigeDatenAn(TADRESS * ta, int anzahl)
{
    int pos;
    for(pos=0;pos<anzahl;pos++)
    {
        printf("Datensatz %d:\n", pos+1);
        printf("\tVorname:      %s\n", (ta+pos)->vname);
        printf("\tNachname:     %s\n", (ta+pos)->nname);
        printf("\tPLZ:          %ld\n",(ta+pos)->PLZ);
        printf("\tOrt:          %s\n", (ta+pos)->ort);
        TDATUM u = (ta+pos)->geburtsjahr;
        printf("\tGeburtsdatum: %d.%d.%d\n", u.tag, u.monat, u.jahr);
        printf("\tGeburtsmonat: %s\n", u.mon_name);
    }
}


TADRESS * einlesen(char * filename, int * anzahl)
{
    FILE *fp = fopen(filename, "r");

    int len = 100;

    if (NULL == fp)
    {
        printf("Fehler: Datei konnte nicht geladen werden!\n");
        return NULL;
    }
    char cAnzahl[100];

    fgets(cAnzahl, len, fp);
    *anzahl = atoi(cAnzahl);
    TADRESS *p;
    p = malloc(*anzahl * sizeof(TADRESS));
    if (NULL == p)
    {
        printf("Fehler: Speicher konnte nicht reserviert werden!\n");
        fclose(fp);
        return NULL;
    }
    int i;
    for (i = 0;i<*anzahl; i++)
    {
        fscanf(fp, "%s", (p+i)->vname);
        fscanf(fp, "%s", (p+i)->nname);
        char plz[50];
        fscanf(fp, "%s", plz);
        (p+i)->PLZ = atol(plz);
        fscanf(fp, "%s", (p+i)->ort);
        char dateString[50];
        fscanf(fp, "%s", dateString);
        char dd[3];
        getSubString(dateString, dd, 0, 2);
        char mm[3];
        getSubString(dateString, mm, 3, 2);
        char yy[5];
        getSubString(dateString, yy, 6, 4);
        (p+i)->geburtsjahr = mache_date(atoi(dd), atoi(mm), atoi(yy));
    }
    fclose(fp);
    return p;
}

int compareName(const void *nameOne, const void *nameTwo)
{
    TADRESS * eins = (TADRESS *)nameOne;
    TADRESS * zwei = (TADRESS *)nameTwo;
    return strcmp(eins->vname, zwei->vname);
}

void sort_name(TADRESS* p, int anzahl)
{
    qsort(p, anzahl, sizeof(TADRESS), compareName);
}

TDATUM mache_date(int t, int m, int j)
{
    TDATUM rueckwert;
    rueckwert.jahr = j;
    rueckwert.monat = m;
    rueckwert.tag = t;
    strcpy(rueckwert.mon_name, monat[m-1]);
    return rueckwert;
}

void help(void)
{
    printf("%s [Option] File\n\n", executableFileName);
    printf("Option     \tBeschreibung\n");
    printf("-h         \tGibt eine kurze Beschreibung der Optionen aus.\n");
    printf("-p         \tAlle Adressen sollen ausgegeben werden.\n");
    printf("-w filename\tEs sollen die Adressen in einem html-File abgelegt werden.\n");
    printf("-s         \tAlle Adressen sollen sortiert nach Namen ausgegeben werden.\n");
    printf("-f muster  \tSortiert alle Adressen nach Namen und suche nach Muster.\n");
}
