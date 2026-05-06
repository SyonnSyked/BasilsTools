#include "../include/DynamicArray2D.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

static bool Array2D_CanMultiply(size_t a, size_t b, size_t* result)
{
    if (result == NULL)
        return false;

    if (a != 0 && b > SIZE_MAX / a)
        return false;

    *result = a * b;
    return true;
}

static bool Array2D_CanAllocate(size_t width, size_t height, size_t elementSize, size_t* outCount)
{
    size_t count = 0;

    if (width == 0 || height == 0 || elementSize == 0)
        return false;

    if (!Array2D_CanMultiply(width, height, &count))
        return false;

    if (count > SIZE_MAX / elementSize)
        return false;

    if (outCount != NULL)
        *outCount = count;

    return true;
}

bool Array2D_Init(DynArray2D* array, size_t width, size_t height, size_t elementSize)
{
    if (array == NULL)
        return false;

    size_t count = 0;

    if (!Array2D_CanAllocate(width, height, elementSize, &count))
        return false;

    if (!Array_Init(&array->buffer, elementSize))
        return false;

    if (!Array_Resize(&array->buffer, count))
    {
        Array_Free(&array->buffer);
        return false;
    }

    array->width = width;
    array->height = height;
    array->elementSize = elementSize;

    return true;
}

void Array2D_Free(DynArray2D* array)
{
    if (array == NULL)
        return;

    Array_Free(&array->buffer);

    array->width = 0;
    array->height = 0;
    array->elementSize = 0;
}

bool Array2D_Resize(DynArray2D* array, size_t newWidth, size_t newHeight)
{
    if (array == NULL)
        return false;

    size_t newCount = 0;

    if (!Array2D_CanAllocate(newWidth, newHeight, array->elementSize, &newCount))
        return false;

    DynArray newData;

    if (!Array_Init(&newData, array->elementSize))
        return false;

    if (!Array_Resize(&newData, newCount))
    {
        Array_Free(&newData);
        return false;
    }

    size_t copyWidth = array->width < newWidth ? array->width : newWidth;
    size_t copyHeight = array->height < newHeight ? array->height : newHeight;

    for (size_t y = 0; y < copyHeight; y++)
    {
        size_t oldIndex = y * array->width;
        size_t newIndex = y * newWidth;

        void* oldRow = (char*)array->buffer.data + oldIndex * array->elementSize;
        void* newRow = (char*)newData.data + newIndex * array->elementSize;

        memcpy(newRow, oldRow, copyWidth * array->elementSize);
    }

    Array_Free(&array->buffer);

    array->buffer = newData;
    array->width = newWidth;
    array->height = newHeight;

    return true;
}

bool Array2D_Fill(DynArray2D* array, const void* value)
{
    if (array == NULL || value == NULL)
        return false;

    for (size_t i = 0; i < array->buffer.count; i++)
    {
        void* destination = Array_Get(&array->buffer, i);

        if (destination == NULL)
            return false;

        memcpy(destination, value, array->elementSize);
    }

    return true;
}

void Array2D_Clear(DynArray2D* array)
{
    if (array == NULL || array->buffer.data == NULL)
        return;

    memset(array->buffer.data, 0, array->buffer.count * array->elementSize);
}

bool Array2D_Copy(DynArray2D* destination, const DynArray2D* source)
{
    if (destination == NULL || source == NULL)
        return false;

    if (!Array2D_Init(destination, source->width, source->height, source->elementSize))
        return false;

    memcpy(destination->buffer.data, source->buffer.data, source->buffer.count * source->elementSize);

    return true;
}

bool Array2D_Move(DynArray2D* destination, DynArray2D* source)
{
    if (destination == NULL || source == NULL)
        return false;

    Array2D_Free(destination);

    destination->buffer = source->buffer;
    destination->width = source->width;
    destination->height = source->height;
    destination->elementSize = source->elementSize;

    source->buffer.data = NULL;
    source->buffer.elementSize = 0;
    source->buffer.count = 0;
    source->buffer.capacity = 0;

    source->width = 0;
    source->height = 0;
    source->elementSize = 0;

    return true;
}

bool Array2D_Set(DynArray2D* array, size_t x, size_t y, const void* value)
{
    if (array == NULL || value == NULL)
        return false;

    size_t index = 0;

    if (!Array2D_GetIndex(array, x, y, &index))
        return false;

    return Array_Set(&array->buffer, index, value);
}

void* Array2D_Get(DynArray2D* array, size_t x, size_t y)
{
    if (array == NULL)
        return NULL;

    size_t index = 0;

    if (!Array2D_GetIndex(array, x, y, &index))
        return NULL;

    return Array_Get(&array->buffer, index);
}

const void* Array2D_GetConst(const DynArray2D* array, size_t x, size_t y)
{
    if (array == NULL)
        return NULL;

    size_t index = 0;

    if (!Array2D_GetIndex(array, x, y, &index))
        return NULL;

    return Array_GetConst(&array->buffer, index);
}

bool Array2D_IsInBounds(const DynArray2D* array, size_t x, size_t y)
{
    if (array == NULL)
        return false;

    return x < array->width && y < array->height;
}

bool Array2D_GetIndex(const DynArray2D* array, size_t x, size_t y, size_t* outIndex)
{
    if (array == NULL || outIndex == NULL)
        return false;

    if (!Array2D_IsInBounds(array, x, y))
        return false;

    *outIndex = y * array->width + x;

    return true;
}

bool Array2D_GetPosition(const DynArray2D* array, size_t index, size_t* outX, size_t* outY)
{
    if (array == NULL || outX == NULL || outY == NULL)
        return false;

    if (index >= array->buffer.count)
        return false;

    *outX = index % array->width;
    *outY = index / array->width;

    return true;
}

size_t Array2D_Count(const DynArray2D* array)
{
    if (array == NULL)
        return 0;

    return array->buffer.count;
}

void Array2D_Destroy(DynArray2D* array) {
     if (array == NULL)
    {
        return;
    }

    free(array->buffer.data);

    array->buffer.data = NULL;
    array->elementSize = 0;
    array->width = 0;
    array->height = 0;
}
