#ifndef DYNAMIC_ARRAY_2D_H
#define DYNAMIC_ARRAY_2D_H

#include <stddef.h>
#include <stdbool.h>

#include "DynamicArray.h"

typedef struct DynArray2D
{
    DynArray buffer;

    size_t width;
    size_t height;
    size_t elementSize;
} DynArray2D;

bool Array2D_Init(DynArray2D* array, size_t width, size_t height, size_t elementSize);
void Array2D_Free(DynArray2D* array);

bool Array2D_Resize(DynArray2D* array, size_t newWidth, size_t newHeight);
bool Array2D_Fill(DynArray2D* array, const void* value);
void Array2D_Clear(DynArray2D* array);

bool Array2D_Copy(DynArray2D* destination, const DynArray2D* source);
bool Array2D_Move(DynArray2D* destination, DynArray2D* source);

bool Array2D_Set(DynArray2D* array, size_t x, size_t y, const void* value);
void* Array2D_Get(DynArray2D* array, size_t x, size_t y);
const void* Array2D_GetConst(const DynArray2D* array, size_t x, size_t y);

bool Array2D_IsInBounds(const DynArray2D* array, size_t x, size_t y);
bool Array2D_GetIndex(const DynArray2D* array, size_t x, size_t y, size_t* outIndex);
bool Array2D_GetPosition(const DynArray2D* array, size_t index, size_t* outX, size_t* outY);

size_t Array2D_Count(const DynArray2D* array);

void Array2D_Destroy(DynArray2D* array);

#endif
