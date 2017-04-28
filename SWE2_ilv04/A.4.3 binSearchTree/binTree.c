/**
 * file: binTree.c
 *
 * Zweck: Implementierung fuer den binaeren Suchbaum
 *
 * date: 2017-04-28
 * progtimeest.: 120 min
 * progtimereal: 120 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung A.4.3
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "binTree.h"

/*
    Fuegt ein Element in den Baum ein
    Parameter:
        - node: Binaerbaum in den der Wert eingetragen werden soll
        - value: der einzutragende Wert
    Rueckgabewert:
        - Adresse auf (KNOTEN *), wenn nicht erfolgreich NULL
*/
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

/*
    Sucht einen Wert in einem binaeren Baum
    Parameter:
        - node: Binaerbaum in den gesucht werden soll
        - value: Wert nach dem gesucht werden soll
    Rueckgabewert:
        - Wenn gefunden Adresse von (KNOTEN *), sonst NULL
*/
KNOTEN * suchen(KNOTEN * node, int value)
{
    if (NULL == node)
        return NULL;

    if (node->wert < value)
        return suchen(node->rechts, value);
    else if (node->wert > value)
        return suchen(node->links, value);
    else
        return node;
}

/*
    Gibt den Speicherplatz von einem binaeren Baum wieder frei
    Parameter:
        node: der freizugebende binaere Baum
*/
void freeTree(KNOTEN * node)
{
    if (NULL == node)
        return;

    freeTree(node->links);
    freeTree(node->rechts);

    free(node);
    node = NULL;
}

/*
    Travesieren: L v R, Ausgabe erfolgt auf stdout
    Parameter:
        - node: der binaere Baum, auf den das Travesieren angewendet werden soll
*/
void inorder_print(KNOTEN * node)
{
    if (NULL == node)
        return;

    inorder_print(node->links);
    printf("\tinorder_print: %d\n", node->wert);
    inorder_print(node->rechts);
}

/*
    Travesieren: L R v, Ausgabe erfolgt auf stdout
    Parameter:
        - node: der binaere Baum, auf den das Travesieren angewendet werden soll
*/
void postorder_print(KNOTEN * node)
{
    if (NULL == node)
        return;

    postorder_print(node->links);
    postorder_print(node->rechts);
    printf("\tpostorder_print: %d\n", node->wert);
}

/*
    Travesieren: v L R, Ausgabe erfolgt auf stdout
    Parameter:
        - node: der binaere Baum, auf den das Travesieren angewendet werden soll
*/
void preorder_print(KNOTEN * node)
{
    if (NULL == node)
        return;

    printf("\tpreorder_print: %d\n", node->wert);
    preorder_print(node->links);
    preorder_print(node->rechts);
}
