#include "../include/DynamicArray.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static bool Array_CanAllocate(size_t count, size_t elementSize)
{
    if (elementSize == 0)
        return false;

    return count <= SIZE_MAX / elementSize;
}

bool Array_Init(DynArray* array, size_t elementSize)
{
    if (array == NULL || elementSize == 0)
        return false;

    array->data = NULL;
    array->elementSize = elementSize;
    array->count = 0;
    array->capacity = 0;

    return true;
}

void Array_Free(DynArray* array)
{
    if (array == NULL)
        return;

    free(array->data);

    array->data = NULL;
    array->elementSize = 0;
    array->count = 0;
    array->capacity = 0;
}

bool Array_Reserve(DynArray* array, size_t newCap)
{
    if (array == NULL)
        return false;

    if (newCap <= array->capacity)
        return true;

    if (!Array_CanAllocate(newCap, array->elementSize))
        return false;

    void* newData = realloc(array->data, newCap * array->elementSize);

    if (newData == NULL)
        return false;

    array->data = newData;
    array->capacity = newCap;

    return true;
}

bool Array_Resize(DynArray* array, size_t newCount)
{
    if (array == NULL)
        return false;

    if (newCount > array->capacity)
    {
        if (!Array_Reserve(array, newCount))
            return false;
    }

    if (newCount > array->count)
    {
        size_t oldByteCount = array->count * array->elementSize;
        size_t newByteCount = newCount * array->elementSize;
        size_t bytesToClear = newByteCount - oldByteCount;

        memset((char*)array->data + oldByteCount, 0, bytesToClear);
    }

    array->count = newCount;

    return true;
}

bool Array_ShrinkToFit(DynArray* array)
{
    if (array == NULL)
        return false;

    if (array->count == array->capacity)
        return true;

    if (array->count == 0)
    {
        free(array->data);
        array->data = NULL;
        array->capacity = 0;
        return true;
    }

    if (!Array_CanAllocate(array->count, array->elementSize))
        return false;

    void* newData = realloc(array->data, array->count * array->elementSize);

    if (newData == NULL)
        return false;

    array->data = newData;
    array->capacity = array->count;

    return true;
}

bool Array_PushBack(DynArray* array, const void* value)
{
    if (array == NULL || value == NULL)
        return false;

    if (array->count >= array->capacity)
    {
        size_t newCap = array->capacity == 0 ? 4 : array->capacity * 2;

        if (newCap < array->capacity)
            return false;

        if (!Array_Reserve(array, newCap))
            return false;
    }

    void* destination = (char*)array->data + array->count * array->elementSize;
    memcpy(destination, value, array->elementSize);

    array->count++;

    return true;
}

bool Array_PopBack(DynArray* array, void* outValue)
{
    if (array == NULL || array->count == 0)
        return false;

    size_t lastIndex = array->count - 1;
    void* source = (char*)array->data + lastIndex * array->elementSize;

    if (outValue != NULL)
        memcpy(outValue, source, array->elementSize);

    array->count--;

    return true;
}


bool Array_Copy(DynArray *destination, const DynArray *source) {
    if (destination == NULL || source == NULL)
        return false;

    if (!Array_Init(destination, source->elementSize))
        return false;

    if (source->count == 0)
        return true;

    if (!Array_Reserve(destination, source->count))
    {
        Array_Free(destination);
        return false;
    }

    memcpy(destination->data, source->data, source->count * source->elementSize);

    destination->count = source->count;

    return true;
}

bool Array_Move(DynArray* destination, DynArray* source) {
    if (destination == NULL || source == NULL)
        return false;

    Array_Free(destination);

    destination->data = source->data;
    destination->elementSize = source->elementSize;
    destination->count = source->count;
    destination->capacity = source->capacity;

    source->data = NULL;
    source->elementSize = 0;
    source->count = 0;
    source->capacity = 0;

    return true;
}


bool Array_Set(DynArray* array, size_t index, const void* value)
{
    if (array == NULL || value == NULL || index >= array->count)
        return false;

    void* destination = (char*)array->data + index * array->elementSize;
    memcpy(destination, value, array->elementSize);

    return true;
}

void* Array_Get(DynArray* array, size_t index)
{
    if (array == NULL || index >= array->count)
        return NULL;

    return (char*)array->data + index * array->elementSize;
}

const void* Array_GetConst(const DynArray* array, size_t index)
{
    if (array == NULL || index >= array->count)
        return NULL;

    return (const char*)array->data + index * array->elementSize;
}

void* Array_Back(DynArray* array)
{
    if (array == NULL || array->count == 0)
        return NULL;

    return Array_Get(array, array->count - 1);
}

const void* Array_BackConst(const DynArray* array)
{
    if (array == NULL || array->count == 0)
        return NULL;

    return Array_GetConst(array, array->count - 1);
}

bool Array_Insert(DynArray* array, size_t index, const void* value)
{
    if (array == NULL || value == NULL || index > array->count)
        return false;

    if (array->count >= array->capacity)
    {
        size_t newCap = array->capacity == 0 ? 4 : array->capacity * 2;

        if (newCap < array->capacity)
            return false;

        if (!Array_Reserve(array, newCap))
            return false;
    }

    void* destination = (char*)array->data + index * array->elementSize;
    void* next = (char*)destination + array->elementSize;

    size_t elementsToMove = array->count - index;
    size_t bytesToMove = elementsToMove * array->elementSize;

    memmove(next, destination, bytesToMove);
    memcpy(destination, value, array->elementSize);

    array->count++;

    return true;
}

bool Array_RemoveAt(DynArray* array, size_t index)
{
    if (array == NULL || index >= array->count)
        return false;

    void* destination = (char*)array->data + index * array->elementSize;
    void* source = (char*)destination + array->elementSize;

    size_t elementsToMove = array->count - index - 1;
    size_t bytesToMove = elementsToMove * array->elementSize;

    memmove(destination, source, bytesToMove);

    array->count--;

    return true;
}

bool Array_RemoveAtSwap(DynArray* array, size_t index)
{
    if (array == NULL || index >= array->count)
        return false;

    size_t lastIndex = array->count - 1;

    if (index != lastIndex)
    {
        void* destination = (char*)array->data + index * array->elementSize;
        void* source = (char*)array->data + lastIndex * array->elementSize;

        memcpy(destination, source, array->elementSize);
    }

    array->count--;

    return true;
}

void Array_Clear(DynArray* array)
{
    if (array == NULL)
        return;

    array->count = 0;
}

void Array_Destroy(DynArray* array)
{
    if (array == NULL)
    {
        return;
    }

    free(array->data);

    array->data = NULL;
    array->elementSize = 0;
    array->count = 0;
    array->capacity = 0;
}
