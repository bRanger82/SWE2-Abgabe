/**
 * file: binTree.h
 *
 * Zweck: Prototypen fuer die Implementierung fuer den binaeren Suchbaum
 *
 * date: 2017-04-28
 * progtimeest.: 120 min
 * progtimereal: 120 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung 4/2
 *
 */

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

// 5. Speicher freigeben
void freeTree(KNOTEN *);
