/**
 * file: TestProgram.h
 *
 * Zweck: Prototypen fuer die Implementierung fuer das Testprogramm fuer den binaeren Suchbaum
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
#include <stdbool.h>
#include "binTree.h"

int getRandNum(int max, bool initRand); //gibt eine Zufallszahl zurueck (Breich 1 bis max)
KNOTEN * createTestValues(int cnt, bool initRand, int maxValue); // Erstellt einen binaeren Baum mit cnt Anzahl Blaetter im Bereich zwischen 1 und maxValue
void printOrder(KNOTEN * root); // Fuehrt das Travesieren von L R v, L v R und v L R aus
KNOTEN * searchValue(KNOTEN * root, int seachValue); // sucht einen Wert in einem binaeren Baum und gibt eine Info auf stdout aus
int getNumberFromStdIn(void); // Liest einen integer Wert von stdin ein
