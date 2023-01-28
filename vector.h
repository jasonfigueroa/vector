#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <string.h>
#include "primitive.h"

#define VECTOR_INITIAL_CAPACITY 5

typedef Object* GenericArray;

typedef struct Vector
{
	GenericArray data;

	uint elementSize;
	uint capacity;
	uint length;

	void (*releaseFunction)(Object);
	void (*printerFunction)(FILE*, Object);
} Vector;

Vector *
vectorInit(uint elementSize);

void
vectorInsert(Vector*, uint pos, Object element);

void
vectorPush(Vector*, Object element);

void
vectorSetRelease(Vector*, void (*releaser)(Object));

void
vectorSetPrinter(Vector*, void (*printer)(FILE*, Object));

void
vectorRelease(Vector*);

void
vectorPrint(FILE* out, Vector*);

static void
vectorDoubleCapacity(Vector* vector)
{
    int newCapacity = vector->capacity * 2;

    GenericArray tmp = realloc(vector->data, newCapacity * sizeof(Object));

    if (!tmp)
    {
        printf("unable to realloc alist->data to tmp");
        exit(1);
    }
    else
    {
        vector->data = tmp;
        vector->capacity = newCapacity;
    }
}

#endif // VECTOR_H_INCLUDED
