#include <stdio.h>
#include <stdlib.h>
#include "eile.h"

int main()
{
    Queue *q = (Queue*) malloc (sizeof(Queue));
    init(q); /* Sukuriam eile*/
    printf("Dydis: ");
    enqueue(q,1); // Idedam 1 i eile
    printf("Dydis: ");
    enqueue(q,2); // Idedam 2 i eile
    printf("Dydis: ");
    enqueue(q,3); // Idedam 3 i eile
    printf("Dydis: ");
    enqueue(q,4); // Idedam 4 i eile
    printf("Dydis: ");
    enqueue(q,5); // Idedam 5 i eile
    printf("Eile: ");
    print_list(q); /* Atspausdina eile */
    printf("Istrinamas 1-asis elementas: ");
    dequeue(q); // istrinam pirma eiles elementa
    printf("Eile: ");
    print_list(q); /* Atspausdina eile be pirmo elemento */
    printf("1-asis eiles elementas: ");
    print_front(q); /* Atspausdina pirma eiles elementa */

    return 0;
}
