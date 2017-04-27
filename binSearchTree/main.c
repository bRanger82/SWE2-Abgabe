#include <stdio.h>
#include <stdlib.h>
#include "binTree.h"

int main(void)
{
   int i, a[] = { 3, 2, 4, 1, 5 };
   KNOTEN *wurzel=NULL;

   for (i=0; i < sizeof(a)/sizeof(int); i++)
   {
      wurzel=einordnen(wurzel, a[i]);
      if (NULL == wurzel)
      {
          printf("Fehler!");
          return EXIT_FAILURE;
      }
   }

   printf("\nInorder   (LVR)\n");
   inorder_print(wurzel);
   printf("\nPostorder (LRV)\n");
   postorder_print(wurzel);
   printf("\nPreorder  (VLR)\n");
   preorder_print(wurzel);

   freeTree(wurzel);
   return EXIT_SUCCESS;
}
