#include <stdio.h>
#include <stdlib.h>
#include "btree.c"
int main(void) {
   KNOTEN *wurzel=NULL;

   do {
      printf("Bitte Zahl eingeben : ");
      scanf("%d",&zahl);
      wurzel=einordnen(wurzel);
   } while(zahl != 0);
   return EXIT_SUCCESS;
}
