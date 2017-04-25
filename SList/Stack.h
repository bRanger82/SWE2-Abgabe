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
