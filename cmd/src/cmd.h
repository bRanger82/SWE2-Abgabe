// Definition der Kommandos welche interpretiert werden koennen
const char * cmdExit = "exit";       // Shell soll beendet werden
const char * cmdCurrDir = "pwd";     // Ausgabe aktuelles Verzeichnis auf stdout
const char * cmdFHSDate = "fhsdate"; // Ausgabe aktuelles Datum auf stdout
const char * cmdFHSTime = "fhstime"; // Ausgabe aktuelle Uhrzeit auf stdout
const char * cmdHelp = "help";       // Ausgabe der Hilfe-Information auf stdout
const char * cmdChangeDir = "cd";    // Aendern des aktuellen Verzeichnisses
// Ende Definition Kommandos

// Definition der Rueckgabe-Werte der Parsing Funktion
#define RET_PARSE_CMD_SYS -12    // Aufruf von system(command)
#define RET_PARSE_CMD_NOT_SET -5 // Eingabe enthaelt nur Wert(e) von DELIMS
#define RET_PARSE_CMD_ERROR -2   // Fehler beim Lesen der Eingabe (falscher Parameter)
#define RET_PARSE_CMD_UNKNOWN -1 // Eingabe unbekannt
#define RET_PARSE_CMD_OK 0       // Eingabe konnte erfolgreich verarbeitet werden
#define RET_PARSE_CMD_EXIT 1     // Der Befehl zum Beenden der Shell
// Ende Definition Rueckgabe-Werte

#define MAX_LENGTH 1024  // Puffer fuer die Eingabe
#define DELIMS " \t\r\n" // Trennzeichen-Erkennung zwischen den Parametern

// Methode, welche das aktuelle Datum und Uhrzeit zurueck liefert
struct tm * getTimeInfo(void)
{
    time_t rawtime;
    time ( &rawtime );
    return localtime ( &rawtime );
}

void showHelp(void);          // Methode, welche die Hilfe auf stdout ausgibt
int parseInput(char * input); // Methode, welche die Eingabe verarbeitet. Rueckgabewerte siehe RET_PARSE_CMD_*
