#include <stdio.h>
#include <stdlib.h>

int rekursiv(int i)
{
    if (i <= 10)
    {
        printf("%d\n", i);
        rekursiv(i + 1);
    }
    return i;
}

int rekSum(int i, int min)
{
    if (i < min)
        return 0;
    else
        return i + rekSum(i-1, min);
}

int rekSum2(int i, int max)
{
    if (i <= max)
    {
        return i + rekSum2(i + 1, max);
    } else
    {
        return 0;
    }
}

int main(int argc, char* argv[])
{
    //Alles was ich mit iteration machen kann kann man auch mit rekursion machen
    printf("Ausgabe Funktion Rekursion:\n");
    rekursiv(5);
    printf("\n");
    printf("Summe (Rekursion): %d\n", rekSum(10, 5));
    printf("\n");
    printf("Summe (Rekursion): %d\n", rekSum2(5, 10));
    printf("\n");
    return EXIT_SUCCESS;
}
