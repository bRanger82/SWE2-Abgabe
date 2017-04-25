/**
 * file: TestProgram.h
 *
 * Zweck: Beinhaltet die Prototypen fuer das Testprogramm
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

// Prototypen fuer den STACK Test
void readNextValueStack(void);  // Liest naechsten Wert aus dem Stack aus und gibt diese Information auf stdout aus
void checkStackSize(void);      // Prueft die Antzahl der Eintrage und gibt diese Information auf stdout aus
void runStackTest(void);        // Testprozedur fuer den Stack

// Prototypen fuer den Queue Test
void readNextValueQueue(void);  // Liest naechsten Wert aus der Queue aus und gibt diese Information auf stdout aus
void checkQueueSize(void);      // Prueft die Antzahl der Eintrage und gibt diese Information auf stdout aus
void runQueueTest(void);        // Testprozedur fuer die Queue

// Prototypen fuer den Double-Ended-Queue Test
void checkDeQueueSize(void);      // Prueft die Antzahl der Eintrage und gibt diese Information auf stdout aus
void readLastValueDeQueue(void);  // Liest den _hinteren_ Wert aus der Double-Ended-Queue aus und gibt diese Information auf stdout aus
void readFirstValueDeQueue(void); // Liest den _vorderen_ Wert aus der Double-Ended-Queue aus und gibt diese Information auf stdout aus
void runDeQueueTest(void);        // Testprozedur fuer die Double-Ended-Queue
