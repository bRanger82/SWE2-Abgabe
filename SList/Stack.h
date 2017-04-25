/**
 * file: Stack.h
 *
 * Zweck: Beinhaltet die Prototypen fuer den Stack
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

/* Prototypes fuer Stack */
void * push(void * data);       //fuege element hinzu
void * pop(void);               //lese element und entferne es aus dem Stack
void * top(void);               //lese oberstes element ohne es zu entfernen
bool Sempty(void);              //prueft, ob der stack leer ist
int Slength (void);             //Maximale laenge des Stacks
void Sdelete(void);             //Zuruecksetzen des Stack und Inhalt wird loeschen
bool checkStackAvailable(void); //Prueft, ob der Stack angelegt und zumindest ein Datensatz vorhanden ist
