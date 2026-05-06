#include "../include/DynamicArray3D.h"

#include <string.h>
#include <stdint.h>

static bool Array3D_CanMultiply(size_t a, size_t b, size_t* result)
{
    if (result == NULL)
        return false;

    if (a != 0 && b > SIZE_MAX / a)
        return false;

    *result = a * b;
    return true;
}

static bool Array3D_CanAllocate(
    size_t width,
    size_t height,
    size_t depth,
    size_t elementSize,
    size_t* outCount
)
{
    size_t widthHeight = 0;
    size_t count = 0;

    if (width == 0 || height == 0 || depth == 0 || elementSize == 0)
        return false;

    if (!Array3D_CanMultiply(width, height, &widthHeight))
        return false;

    if (!Array3D_CanMultiply(widthHeight, depth, &count))
        return false;

    if (count > SIZE_MAX / elementSize)
        return false;

    if (outCount != NULL)
        *outCount = count;

    return true;
}

bool Array3D_Init(DynArray3D* array, size_t width, size_t height, size_t depth, size_t elementSize)
{
    if (array == NULL)
        return false;

    size_t count = 0;

    if (!Array3D_CanAllocate(width, height, depth, elementSize, &count))
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
    array->depth = depth;
    array->elementSize = elementSize;

    return true;
}

void Array3D_Free(DynArray3D* array)
{
    if (array == NULL)
        return;

    Array_Free(&array->buffer);

    array->width = 0;
    array->height = 0;
    array->depth = 0;
    array->elementSize = 0;
}

bool Array3D_Resize(DynArray3D* array, size_t newWidth, size_t newHeight, size_t newDepth)
{
    if (array == NULL)
        return false;

    size_t newCount = 0;

    if (!Array3D_CanAllocate(newWidth, newHeight, newDepth, array->elementSize, &newCount))
        return false;

    DynArray newBuffer;

    if (!Array_Init(&newBuffer, array->elementSize))
        return false;

    if (!Array_Resize(&newBuffer, newCount))
    {
        Array_Free(&newBuffer);
        return false;
    }

    size_t copyWidth = array->width < newWidth ? array->width : newWidth;
    size_t copyHeight = array->height < newHeight ? array->height : newHeight;
    size_t copyDepth = array->depth < newDepth ? array->depth : newDepth;

    for (size_t z = 0; z < copyDepth; z++)
    {
        for (size_t y = 0; y < copyHeight; y++)
        {
            size_t oldIndex = z * array->width * array->height + y * array->width;
            size_t newIndex = z * newWidth * newHeight + y * newWidth;

            void* oldRow = (char*)array->buffer.data + oldIndex * array->elementSize;
            void* newRow = (char*)newBuffer.data + newIndex * array->elementSize;

            memcpy(newRow, oldRow, copyWidth * array->elementSize);
        }
    }

    Array_Free(&array->buffer);

    array->buffer = newBuffer;
    array->width = newWidth;
    array->height = newHeight;
    array->depth = newDepth;

    return true;
}

bool Array3D_Fill(DynArray3D* array, const void* value)
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

void Array3D_Clear(DynArray3D* array)
{
    if (array == NULL || array->buffer.data == NULL)
        return;

    memset(array->buffer.data, 0, array->buffer.count * array->elementSize);
}

bool Array3D_Copy(DynArray3D* destination, const DynArray3D* source)
{
    if (destination == NULL || source == NULL)
        return false;

    if (!Array3D_Init(destination, source->width, source->height, source->depth, source->elementSize))
        return false;

    memcpy(
        destination->buffer.data,
        source->buffer.data,
        source->buffer.count * source->elementSize
    );

    return true;
}

bool Array3D_Move(DynArray3D* destination, DynArray3D* source)
{
    if (destination == NULL || source == NULL)
        return false;

    Array3D_Free(destination);

    destination->buffer = source->buffer;
    destination->width = source->width;
    destination->height = source->height;
    destination->depth = source->depth;
    destination->elementSize = source->elementSize;

    source->buffer.data = NULL;
    source->buffer.elementSize = 0;
    source->buffer.count = 0;
    source->buffer.capacity = 0;

    source->width = 0;
    source->height = 0;
    source->depth = 0;
    source->elementSize = 0;

    return true;
}

bool Array3D_Set(DynArray3D* array, size_t x, size_t y, size_t z, const void* value)
{
    if (array == NULL || value == NULL)
        return false;

    size_t index = 0;

    if (!Array3D_GetIndex(array, x, y, z, &index))
        return false;

    return Array_Set(&array->buffer, index, value);
}

void* Array3D_Get(DynArray3D* array, size_t x, size_t y, size_t z)
{
    if (array == NULL)
        return NULL;

    size_t index = 0;

    if (!Array3D_GetIndex(array, x, y, z, &index))
        return NULL;

    return Array_Get(&array->buffer, index);
}

const void* Array3D_GetConst(const DynArray3D* array, size_t x, size_t y, size_t z)
{
    if (array == NULL)
        return NULL;

    size_t index = 0;

    if (!Array3D_GetIndex(array, x, y, z, &index))
        return NULL;

    return Array_GetConst(&array->buffer, index);
}

bool Array3D_IsInBounds(const DynArray3D* array, size_t x, size_t y, size_t z)
{
    if (array == NULL)
        return false;

    return x < array->width && y < array->height && z < array->depth;
}

bool Array3D_GetIndex(const DynArray3D* array, size_t x, size_t y, size_t z, size_t* outIndex)
{
    if (array == NULL || outIndex == NULL)
        return false;

    if (!Array3D_IsInBounds(array, x, y, z))
        return false;

    size_t layerSize = 0;
    size_t zOffset = 0;
    size_t yOffset = 0;
    size_t index = 0;

    if (!Array3D_CanMultiply(array->width, array->height, &layerSize))
        return false;

    if (!Array3D_CanMultiply(z, layerSize, &zOffset))
        return false;

    if (!Array3D_CanMultiply(y, array->width, &yOffset))
        return false;

    if (zOffset > SIZE_MAX - yOffset)
        return false;

    index = zOffset + yOffset;

    if (index > SIZE_MAX - x)
        return false;

    index += x;

    if (index >= array->buffer.count)
        return false;

    *outIndex = index;

    return true;
}

bool Array3D_GetPosition(
    const DynArray3D* array,
    size_t index,
    size_t* outX,
    size_t* outY,
    size_t* outZ
)
{
    if (array == NULL || outX == NULL || outY == NULL || outZ == NULL)
        return false;

    if (index >= array->buffer.count)
        return false;

    size_t layerSize = array->width * array->height;

    *outZ = index / layerSize;

    size_t localIndex = index % layerSize;

    *outY = localIndex / array->width;
    *outX = localIndex % array->width;

    return true;
}

size_t Array3D_Count(const DynArray3D* array)
{
    if (array == NULL)
        return 0;

    return array->buffer.count;
}
