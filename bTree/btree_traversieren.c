/* btree_traversieren.c 
   siehe http://openbook.rheinwerk-verlag.de/c_von_a_bis_z/022_c_algorithmen_004.htm */
#include <stdio.h>
#include <stdlib.h>

struct knoten{
   int wert;
   struct knoten *links;
   struct knoten *rechts;
};
typedef struct knoten KNOTEN;

/* Traversieren bedeutet jeden Knoten genau einmal aufsuchen
   Sei:
   L/R   Bewegung nach Links/Rechts
   V     einen Knoten besuchen (visit)

   Dann ist:
   L V R   inorder
   L R V   postorder
   V L R   preorder
*/
void inorder_print(KNOTEN *zeiger)
{ /* LVR */      
	if (zeiger != NULL)
	   {
	   inorder_print(zeiger->links);
	   printf("%d->",zeiger->wert);
	   inorder_print(zeiger->rechts);
	   }
	return;
}

void postorder_print(KNOTEN *zeiger)
{ /* LRV */
	if (zeiger != NULL)
	   {
	   postorder_print(zeiger->links);
	   postorder_print(zeiger->rechts);
	   printf("%d->",zeiger->wert);
	   }
	return;
}

void preorder_print(KNOTEN *zeiger)
{ /* VLR */
	if (zeiger != NULL)
	   {
	   printf("%d->",zeiger->wert);
	   preorder_print(zeiger->links);
	   preorder_print(zeiger->rechts);
	   }
	return;
}

KNOTEN *einordnen(KNOTEN *zeiger, int zahl)  {
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
      zeiger->links=einordnen(zeiger->links, zahl);
   else if(zeiger->wert < zahl)
      zeiger->rechts=einordnen(zeiger->rechts, zahl);
   return (zeiger);
}

int main(void) {
   int i, a[] = { 3, 2, 4, 1, 5 };
   KNOTEN *wurzel=NULL;

   for (i=0; i < sizeof(a)/sizeof(int); i++)
      wurzel=einordnen(wurzel, a[i]);       

   printf("\nInorder   (LVR)\n");
   inorder_print(wurzel);
   printf("\nPostorder (LRV)\n");
   postorder_print(wurzel);
   printf("\nPreorder  (VLR)\n");
   preorder_print(wurzel);

   return EXIT_SUCCESS;
}
