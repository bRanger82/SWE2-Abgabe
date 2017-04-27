#include <stdio.h>
#include <stdlib.h>
#include "binTree.h"

KNOTEN * einordnen(KNOTEN * node, int value)
{
    if (NULL == node)
    {
        node = (KNOTEN *)malloc(sizeof(KNOTEN));
        if (NULL == node)
            return NULL; // Konnte nicht erstellt werden

        node->wert = value;
        node->links = NULL;
        node->rechts = NULL;
    } else if (node->wert >= value)
    {
        node->links = einordnen(node->links, value);
    } else
    {
        node->rechts = einordnen(node->rechts, value);
    }
    return node;
}

void freeTree(KNOTEN * node)
{
    if (NULL == node)
        return;

    freeTree(node->links);
    freeTree(node->rechts);

    free(node);
}

// L v R
void inorder_print(KNOTEN * node)
{
    if (NULL == node)
        return;

    inorder_print(node->links);
    printf("\tinorder_print: %d\n", node->wert);
    inorder_print(node->rechts);
}

// L R v
void postorder_print(KNOTEN * node)
{
    if (NULL == node)
        return;

    postorder_print(node->links);
    postorder_print(node->rechts);
    printf("\tpostorder_print: %d\n", node->wert);
}

// v L R
void preorder_print(KNOTEN * node)
{
    if (NULL == node)
        return;

    printf("\tpreorder_print: %d\n", node->wert);
    preorder_print(node->links);
    preorder_print(node->rechts);
}
