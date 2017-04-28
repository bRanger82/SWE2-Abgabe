#include <stdlib.h>
#include <stdbool.h>
#include "binTree.h"

int getRandNum(int max, bool initRand);
KNOTEN * createTestValues(int cnt, bool initRand);
void printOrder(KNOTEN * root);
KNOTEN * searchValue(KNOTEN * root, int seachValue);
int getNumberFromStdIn(void);
