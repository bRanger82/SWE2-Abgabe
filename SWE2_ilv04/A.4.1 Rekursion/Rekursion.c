/**
 * file: Rekursion.c
 *
 * Zweck: Beinhaltet den Programm-Code fuer den Einstieg in die Rekursion
 *
 * date: 2017-04-26
 * progtimeest.: 30 min
 * progtimereal: 30 min
 * author: Michael Bieringer
 * email: Michael.Bieringer@gmx.net
 *
 * Salzburg University of Applied Sciences
 * Information Technology & Systems Management
 * SWE2 2017 Uebung A.4.1
 *
 */

#include <stdio.h>
#include <stdlib.h>

// Rekursive Ausgabe von i bis 10
int rekursiv(int i)
{
    if (i <= 10)
    {
        printf("%d\n", i);
        rekursiv(i + 1);
    }
    return i;
}

// Berechnung Summe mittels Rekursion (mit Minimum)
int rekSumMin(int i, int min)
{
    if (i < min)
        return 0;
    else
        return i + rekSumMin(i-1, min);
}

// Berechnung Summe mittels Rekursion (mit Maximum)
int rekSumMax(int i, int max)
{
    if (i <= max)
        return i + rekSumMax(i + 1, max);
    else
        return 0;
}

int main(int argc, char* argv[])
{
    //Alles was ich mit iteration machen kann kann man auch mit rekursion machen

    // Rekursion, Zahlen von 5 - 10 auf stdout ausgeben
    printf("Ausgabe Funktion Rekursion:\n");
    rekursiv(5);
    printf("\n");

    // Summe berechnen mit Rekursion
    printf("Summe (Rekursion - rekSumMin): %d\n", rekSumMin(10, 5));
    printf("\n");

    // Summe berechnen mit Rekursion, Variante 2
    printf("Summe (Rekursion - rekSumMax): %d\n", rekSumMax(5, 10));
    printf("\n");

    return EXIT_SUCCESS;
}
