#include <stdio.h>
#include <stdbool.h>

// Hinzufügen eines neuen Eintrags in den DEQUEUE Speicher
void * DQ_insert_element_at_back(void *);
// Holen eines Eintrags aus dem DEQUEUE Speicher
void * DQ_remove_element_at_back(void);
// Hinzufügen eines neuen Eintrags in den DEQUEUE Speicher
void * DQ_insert_element_at_front(void *);
// Holen eines Eintrags aus dem DEQUEUE Speicher
void * DQ_remove_element_at_front(void);
// Abfragen des ersten Element
void * DQ_examine_first_element(void);
// Abfragen des letzten Element
void * DQ_examine_last_element(void);
// Abfragen, ob DEQUEUE Speicher leer ist
bool DQ_empty(void);
// Löschen des gesamten DEQUEUE Speichers
void DQ_delete(void);
