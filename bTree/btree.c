/* btree1.c
   siehe http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/022_c_algorithmen_004.htm */
#include <stdio.h>
#include <stdlib.h>

struct knoten{
   int wert;
   struct knoten *links;
   struct knoten *rechts;
};
typedef struct knoten KNOTEN;

/* globale Variable */
int zahl;

KNOTEN *einordnen(KNOTEN *zeiger)  {
   if(zeiger == NULL) {
      zeiger = malloc(sizeof(KNOTEN));
      if(zeiger==NULL) {
         printf("Konnte keinen Speicherplatz reservieren!\n");
         exit (EXIT_FAILURE);
      }
      zeiger->wert=zahl;
      zeiger->links=zeiger->rechts=NULL;
   }
   else if(zeiger->wert >= zahl)
      zeiger->links=einordnen(zeiger->links);
   else if(zeiger->wert < zahl)
      zeiger->rechts=einordnen(zeiger->rechts);
   return (zeiger);
}

