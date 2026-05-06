#ifndef DYNAMIC_ARRAY_3D_H
#define DYNAMIC_ARRAY_3D_H

#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>

#include "DynamicArray.h"

typedef struct DynArray3D
{
    DynArray buffer;

    size_t width;
    size_t height;
    size_t depth;
    size_t elementSize;
} DynArray3D;

bool Array3D_Init(DynArray3D* array, size_t width, size_t height, size_t depth, size_t elementSize);
void Array3D_Free(DynArray3D* array);

bool Array3D_Resize(DynArray3D* array, size_t newWidth, size_t newHeight, size_t newDepth);
bool Array3D_Fill(DynArray3D* array, const void* value);
void Array3D_Clear(DynArray3D* array);

bool Array3D_Copy(DynArray3D* destination, const DynArray3D* source);
bool Array3D_Move(DynArray3D* destination, DynArray3D* source);

bool Array3D_Set(DynArray3D* array, size_t x, size_t y, size_t z, const void* value);
void* Array3D_Get(DynArray3D* array, size_t x, size_t y, size_t z);
const void* Array3D_GetConst(const DynArray3D* array, size_t x, size_t y, size_t z);

bool Array3D_IsInBounds(const DynArray3D* array, size_t x, size_t y, size_t z);
bool Array3D_GetIndex(const DynArray3D* array, size_t x, size_t y, size_t z, size_t* outIndex);
bool Array3D_GetPosition(const DynArray3D* array, size_t index, size_t* outX, size_t* outY, size_t* outZ);

size_t Array3D_Count(const DynArray3D* array);

void Array3D_Destroy(DynArray3D* array);

#endif
