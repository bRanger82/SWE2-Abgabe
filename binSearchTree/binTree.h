#include <stdlib.h>

struct knoten
{
    int wert;               // Daten
    struct knoten * links;  // Zeiger auf linken Teilbaum
    struct knoten * rechts; // Zeiger auf rechten Teilbaum
};
typedef struct knoten KNOTEN;

// 2. Interface (Zugriffsfunktionen) definieren
// Einfuegene
KNOTEN * einordnen(KNOTEN * , int );

// 3. Travesieren
void inorder_print(KNOTEN *);   // L v R
void postorder_print(KNOTEN *); // L R v
void preorder_print(KNOTEN *);  // v L R

// 4. Suchen
KNOTEN * suchen(KNOTEN * , int );

void freeTree(KNOTEN *);
