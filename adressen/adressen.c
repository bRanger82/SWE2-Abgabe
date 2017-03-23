#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


void help(void);
TDATUM mache_date(int t, int m, int j);
TADRESS * einlesen(char * filename, int * anzahl);
void ausgabe(TADRESS* p, int anzahl, char * filename);
void ausgabe_html(TADRESS* p, int anzahl);
void sort_name(TADRESS* p, int anzahl);
// Sortiert alle Adressen nach Namen
void suche_name(TADRESS* p, int anzahl, char *name);
// Sortiert alle Adressen nach Namen und durchse diese

char * executableFileName;
const char * monat[12] = {"Jan", "Feb", "Mar", "Apr", "Mai", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dez"};

TDATUM mache_date(int t, int m, int j)
{
    TDATUM rueckwert;
    rueckwert.jahr = j;
    rueckwert.monat = m;
    rueckwert.tag = t;
    strcpy(rueckwert.mon_name, monat[m-1]);
    return rueckwert;
}


char* getSubString(char* inputString, char* subString, int index, int subStringLength)
{
    int counter, inputStringLength = strlen(inputString);

    if(index < 0 || index > inputStringLength ||
          (index + subStringLength) > inputStringLength){
        printf("Invalid Input");
        return NULL;
    }

    for(counter = 0; counter < subStringLength; counter++){
        subString[counter] = inputString[index++];
    }

    subString[counter] = '\0';

    return subString;
}


void testRead(char * adressentxt)
{
    FILE *fp = fopen(adressentxt, "r");

    int len = 100;

    if (NULL == fp)
    {
        printf("Error: Filehandle is NULL!\n");
        return;
    }

    printf("Filename: %s\n", adressentxt);
    char cAnzahl[100];

    fgets(cAnzahl, len, fp);
    //fscanf(fp, "%s", *cAnzahl);

    printf("Wert von cAnzahl: %s\n", cAnzahl);
    int iAnzahl = atoi(cAnzahl);
    TADRESS *p;
    p = malloc(iAnzahl * sizeof(TADRESS));
    if (NULL == p)
    {
        printf("Fehler: Speicher konnte nicht reserviert werden!\n");
        fclose(fp);
        return;
    }
    int i;
    for (i = 0;i<iAnzahl; i++)
    {
        fscanf(fp, "%s", (p+i)->vname);
        fscanf(fp, "%s", (p+i)->nname);
        char x[50];
        fscanf(fp, "%s", x);
        (p+i)->PLZ = atol(x);
        fscanf(fp, "%s", (p+i)->ort);
        char c[50];
        fscanf(fp, "%s", c);
        char dd[2];
        getSubString(c, dd, 0, 2);
        char mm[2];
        getSubString(c, mm, 3, 2);
        char yy[4];
        getSubString(c, yy, 6, 4);
        (p+i)->geburtsjahr = mache_date(atoi(dd), atoi(mm), atoi(yy));

        printf("vname: %s\n", (p+i)->vname);
        printf("nname: %s\n", (p+i)->nname);
        printf("PLZ:   %ld\n",(p+i)->PLZ);
        printf("Ort:   %s\n", (p+i)->ort);
        TDATUM u = (p+i)->geburtsjahr;
        printf("Geburtsdaten: %d.%d.%d %s\n", u.tag, u.monat, u.jahr, u.mon_name);
    }
    fclose(fp);
    free(p);

    return;

}


int main(int argc, char * argv[])
{

    executableFileName = argv[0];
    help();
    testRead("C:\\Temp\\adressen.txt");
    return EXIT_SUCCESS;



    int i = 0;
    char * filename = NULL;
    //Minimale Anzahl Parameter pruefen
    if (argc < 2)
    {
        help();
        return EXIT_FAILURE;
    }

    //Parameter einlesen
    while(NULL != argv[i])
    {
        if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "-H") == 0)
        {
            help();
            return EXIT_SUCCESS;
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "-D") == 0)
        {

        } else if (strcmp(argv[i], "-a") == 0 || strcmp(argv[i], "-A") == 0)
        {

        }
        if ((argc - 1) == i)
        {
            filename = argv[i];
        }
        i++;
    }
    //Pruefung ob Dateiname als Parameter gesetzt wurde
    if (NULL == filename)
    {
        help();
        return EXIT_FAILURE;
    }

    help();
    printf("Hello world!\n");
    return 0;
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

