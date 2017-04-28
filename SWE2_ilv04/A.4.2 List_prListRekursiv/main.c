/**
 * file: main.c
 *
 * Zweck: Ausfuehrendes Programm
 *
 * date: 2017-04-28
 * progtimeest.: 120 min
 * progtimereal: 120 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung A.4.2
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Liste.h"

int main()
{
    SLIST_HEADER * h = createSList();
    int i = 0;

    for (i=0; i<5; i++)
    {
        int * tmp = (int *) malloc(sizeof(int));
        memcpy(tmp, &i, sizeof(int));
        insertFirst(h, tmp);
    }

    pr_SList(h);
    pr_SListRek(h->First);
    rm_SList(h);
    return EXIT_SUCCESS;
}
