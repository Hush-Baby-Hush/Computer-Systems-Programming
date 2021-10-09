#include "vector.h"
#include <stdlib.h>


vector_t * createVector(int initialSize)
{
    vector_t* create_ = (vector_t*) malloc(sizeof(vector_t));
    create_->array = (int*) malloc(initialSize);
    create_->size = 0;
    create_->maxSize = initialSize;
    return create_;
}

void destroyVector(vector_t * vector)
{
    free(vector->array);
    free(vector);
}

void resize(vector_t * vector)
{
    vector->maxSize *=2;
    vector->array = (int*) realloc(vector->array,vector->maxSize);
}

void push_back(vector_t * vector, int element)
{
    if (vector->size+1 > vector->maxSize)
    {
        resize(vector);
    }
    vector->array[vector->size] = element;
    vector->size++;
    
}

int pop_back(vector_t * vector)
{
    if (vector->size ==0)
    {
        return 0;
    }
    int element = vector->array[vector->size-1];
    vector->array[vector->size-1] = 0;
    vector->size --;
    return element;
}

int access(vector_t * vector, int index)
{
    if (index > vector->size-1)
    {
        return 0;
    }
    int element = vector->array[index];
    return element;
    
}

