#include <stdlib.h>
#include <stdbool.h>

void * DQ_insert_element_at_back(void *);   // Hinzufügen eines neuen Eintrags in den DEQUEUE Speicher
void * DQ_remove_element_at_back(void);     // Holen eines Eintrags aus dem DEQUEUE Speicher
void * DQ_insert_element_at_front(void *);  // Hinzufügen eines neuen Eintrags in den DEQUEUE Speicher
void * DQ_remove_element_at_front(void);    // Holen eines Eintrags aus dem DEQUEUE Speicher
void * DQ_examine_first_element(void);      // Abfragen des ersten Element
void * DQ_examine_last_element(void);       // Abfragen des letzten Element
bool DQ_empty(void);                        // Abfragen, ob DEQUEUE Speicher leer ist
void DQ_delete(void);                       // Löschen des gesamten DEQUEUE Speichers
bool checkDeQueueAvailable(void);           // Prueft, ob die DeQueue angelegt und zumindest ein Datensatz vorhanden ist
