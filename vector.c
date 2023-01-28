#include "vector.h"

/**
 * Initializes a new vector.
 *
 * @param {uint} Unsigned integer with value of the element size to be used for the vector data elements.
 * @returns Allocated vector with initial values, including Object pointer (data) with allocated space for an Object.
 */
Vector *
vectorInit(uint elementSize)
{
    uint capacity = VECTOR_INITIAL_CAPACITY;

	Vector* vector = (Vector*)malloc(sizeof(Vector));

	vector->data = (GenericArray)calloc(capacity, sizeof(Object));

	vector->elementSize = elementSize;
	vector->capacity = capacity;
	vector->length = 0;

	return vector;
}

/**
 * Inserts a new element at position i. It's assumed that position i is less than or equal to the length of the vector.
 *
 * @param {Vector*} Pointer to initialized vector.
 * @param {uint} Index to be used to insert value.
 * @param {Object} Element to be inserted at position i.
 * @returns void.
 */
void
vectorInsert(Vector* vector, uint newElementIndex, Object element)
{
	uint lastElementIndex = vector->length - 1;

	if (newElementIndex > vector->length)
	{
        printf("new element index must be less than or equal to vector->length");
        exit(2);
	}

	if (vector->length == vector->capacity)
	{
        vectorDoubleCapacity(vector);
	}

	// The following should always be true, leaving the check for now for sanity
	if (!vector->data[lastElementIndex +1])
	{
        vector->data[lastElementIndex + 1] = malloc(vector->elementSize);
	}

	uint currentPosition = lastElementIndex;

	while (currentPosition > newElementIndex)
	{
        memcpy(vector->data[currentPosition + 1], vector->data[currentPosition], vector->elementSize);
        --currentPosition;
	}

	if (newElementIndex != vector->length)
	{
        memcpy(vector->data[newElementIndex + 1], vector->data[newElementIndex], vector->elementSize);
	}

	memcpy(vector->data[newElementIndex], element, vector->elementSize);

	vector->length++;
}

/**
 * Appends a new element at the end of a vector.
 *
 * @param {Vector*} Pointer to initialized vector.
 * @param {Object} Element to be appended at the end of the vector.
 * @returns void.
 */
void
vectorPush(Vector* vector, Object element)
{
	if (vector->length == vector->capacity)
	{
        vectorDoubleCapacity(vector);
	}

	if (!vector->data[vector->length])
	{
		vector->data[vector->length] = malloc(vector->elementSize);
	}

	memcpy(vector->data[vector->length], element, vector->elementSize);

	vector->length++;
}

/**
 * Sets the callback function to be used when releasing (freeing) a vector element.
 *
 * @param {Vector*} Pointer to initialized vector.
 * @param {func} Function pointer.
 * @returns void.
 */
void
vectorSetRelease(Vector* vector, void (*releaser)(Object))
{
	vector->releaseFunction = releaser;
}

/**
 * Sets the callback function to be used when printing a vector element.
 *
 * @param {Vector*} Pointer to initialized vector.
 * @param {func} Function pointer.
 * @returns void.
 */
void
vectorSetPrinter(Vector* vector, void (*printer)(FILE*, Object))
{
	vector->printerFunction = printer;
}

/**
 * Iteratively releases, via a callback function, each element in the vector before releasing the vector itself.
 *
 * @param {Vector*} Pointer to initialized vector.
 * @returns void.
 */
void
vectorRelease(Vector* vector)
{
	if (vector)
	{
		if (vector->data)
		{
			uint i = 0;

			for (i = 0; i < vector->length; ++i)
			{
				vector->releaseFunction(vector->data[i]);
			}
		}

		free(vector);
	}
}

/**
 * Iteratively prints, via a callback function, each element in the vector along with some vector metadata.
 *
 * @param {Vector*} Pointer to initialized vector.
 * @returns void.
 */
void
vectorPrint(FILE* out, Vector* vector)
{
	fprintf(out, "Vector info:\nlength = %d\ncapacity = %d\ndata = {", vector->length, vector->capacity);

	for (int i = 0; i < vector->length; ++i)
	{
		vector->printerFunction(out, vector->data[i]);

		if (i != vector->length - 1)
		{
			fprintf(out, ", ");
		}
	}

	fprintf(out, "}\n");
}
