// Definition der Kommandos welche interpretiert werden koennen
const char * cmdExit = "exit";       // Shell soll beendet werden
const char * cmdCurrDir = "pwd";     // Ausgabe aktuelles Verzeichnis auf stdout
const char * cmdFHSDate = "fhsdate"; // Ausgabe aktuelles Datum auf stdout
const char * cmdFHSTime = "fhstime"; // Ausgabe aktuelle Uhrzeit auf stdout
const char * cmdHelp = "help";       // Ausgabe der Hilfe-Information auf stdout
const char * cmdChangeDir = "cd";    // Aendern des aktuellen Verzeichnisses
const char * cmdEcho = "echo";       // Ausgabe von Text auf stdout
const char * cmdPushDir = "pushdir"; // Ablegen eines Verzeichnisses
const char * cmdPopDir = "popdir";   // Auslesen des Verzeichnisses welches mit pushdir abgelegt wurde
const char * cmdListDir = "ls";	     // Zeige das Inhaltsverzeichnis an
const char * cmdGetLCode = "echo$?";// Gibt den Errorcode des zuletzt ausgefuehrten Befehls aus
// Ende Definition Kommandos

// Definition Farbausgabe printf()
#define NORMAL_COLOR  "\x1B[0m"
#define GREEN         "\x1B[32m"
#define BLUE          "\x1B[34m"
#define MANGAN        "\x1B[35m"
// Ende Definition Farbausgabe

// Bitmaske fuer die ls Parameter
#define MASK_LS_a 1
#define MASK_LS_l 2
// Ende Bitmaske fuer ls

// Definition der Rueckgabe-Werte der Parsing Funktion
#define RET_PARSE_CMD_SYS -12    // Aufruf von system(command)
#define RET_PARSE_CMD_NOT_SET -5 // Eingabe enthaelt nur Wert(e) von DELIMS
#define RET_PARSE_CMD_ERROR -2   // Fehler beim Lesen der Eingabe (falscher Parameter)
#define RET_PARSE_CMD_UNKNOWN -1 // Eingabe unbekannt
#define RET_PARSE_CMD_OK 0       // Eingabe konnte erfolgreich verarbeitet werden
#define RET_PARSE_CMD_EXIT 1     // Der Befehl zum Beenden der Shell
// Ende Definition Rueckgabe-Werte

// Definition Rueckgabe-Werte fuer FORK
#define RET_FORK_OK   0
#define RET_FORK_ERR -1
// Ende Definition Rueckgabe-Werte fuer FORK

#define MAX_LENGTH 1024   // Puffer fuer die Eingabe
#define DELIMS " \t\r\n"  // Trennzeichen-Erkennung zwischen den Parametern
#define ECHO_DELIMS " \t" // Trennzeichen-Erkennung fuer den echo Befehl

// Methode, welche das aktuelle Datum und Uhrzeit zurueck liefert
struct tm * getTimeInfo(void)
{
    time_t rawtime;
    time ( &rawtime );
    return localtime ( &rawtime );
}

void showHelp(void);          // Methode, welche die Hilfe auf stdout ausgibt
int parseInput(char * input, char * envp[]); // Methode, welche die Eingabe verarbeitet. Rueckgabewerte siehe RET_PARSE_CMD_*
int execute(char * command, char * params);		  // Kind-Prozess erzeugen
void removeSubstring(char *s,const char *toremove);
bool FileExist(char * path);
bool findExecutable(char * values, char * found, char * command);
