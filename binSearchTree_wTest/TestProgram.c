#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "TestProgram.h"

int getRandNum(int max, bool initRand)
{
    if (initRand)
        srand(time(NULL));

    return (rand() % (max-1)) + 1;
}

KNOTEN * createTestValues(int cnt, bool initRand)
{
    int pos;
    KNOTEN * wurzel = NULL;

    for (pos=0; pos < cnt; pos++)
    {
        wurzel=einordnen(wurzel, getRandNum(200, initRand));
        if (NULL == wurzel)
            return NULL;

    }
    return wurzel;
}

void printOrder(KNOTEN * root)
{
    if (NULL == root)
        return;

    printf("\nInorder   (LVR)\n");
    inorder_print(root);
    printf("\nPostorder (LRV)\n");
    postorder_print(root);
    printf("\nPreorder  (VLR)\n");
    preorder_print(root);
}

KNOTEN * searchValue(KNOTEN * root, int seachValue)
{
    if (NULL == root)
        return NULL;

    printf("\nSuche nach Wert %d ...\n", seachValue);

    KNOTEN * find = suchen(root, seachValue);
    if (NULL == find)
        printf("\tWert '%d' konnte nicht gefunden.\n", seachValue);
    else
        printf("\tWert '%d' gefunden!\n", seachValue);

    return find;
}

int getNumberFromStdIn(void)
{
    int readInVal;
    int result = scanf("%d", &readInVal);

    if (result == EOF) {
        return 0;
    }
    if (result == 0) {
        while (fgetc(stdin) != '\n') // Read until a newline is found
            ;
    }
    return readInVal;
}
