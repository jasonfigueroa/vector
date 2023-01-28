#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main()
{
    Vector* vector = vectorInit(sizeof(int));

    vectorSetRelease(vector, &releasePrimitive);
    vectorSetPrinter(vector, &printInt);

    int x = 1;

    vectorPush(vector, &x);
    x++;

    vectorPush(vector, &x);
    x++;

    vectorPush(vector, &x);
    x++;

    vectorPush(vector, &x);
    x++;

    vectorPush(vector, &x);
    x++;

    vectorInsert(vector, vector->length, &x);

    vectorPrint(stdout, vector);

    vectorRelease(vector);

    return 0;
}
