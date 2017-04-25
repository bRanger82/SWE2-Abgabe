/**
 * file: Queue.h
 *
 * Zweck: Beinhaltet die Prototypen fuer die Queue
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

#include <stdlib.h>
#include <stdbool.h>

//Definition Queue

void * put(void *);               // Hinzufuegen eines neuen Eintrags
void * get(void);                 // Holen eines Eintrags aus dem FIFO Speicher und entfernt es
void * last(void);                // Abfragen des letztes hinzugefuegtem Element ohne es zu entfernen
void * next(void);                // Abfragen des naechsten Elements ohne es zu entfernen
bool Qempty(void);                // Abfragen, ob FIFO Speicher leer ist
int Qlength(void);                // Abfragen, wieviele Eintrage im FIFO Speicher abgelegt sind
void Qdelete(void);               // Loeschen des gesamten FIFO Speichers
bool checkQueueAvailable(void);   // Prueft, ob die Queue NULL oder leer (Len==0) ist (return false), sonst return true
