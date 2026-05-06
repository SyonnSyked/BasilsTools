#include <stdbool.h>

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#define DEFAULT_ARRAYSIZE 16

typedef struct DynArray {
    void* data;
    size_t elementSize;
    size_t count;
    size_t capacity;
} DynArray;

bool Array_Init(DynArray* array, size_t elementSize);
void Array_Free(DynArray* array);

bool Array_Reserve(DynArray* array, size_t newCap);
bool Array_Resize(DynArray* array, size_t newCount);
bool Array_ShrinkToFit(DynArray* array);

bool Array_PushBack(DynArray* array, const void* value);
bool Array_PopBack(DynArray* array, void* outValue);

bool Array_Copy(DynArray* destination, const DynArray* source);
bool Array_Move(DynArray* destination, DynArray* source);

bool Array_Set(DynArray* array, size_t index, const void* value);
void* Array_Get(DynArray* array, size_t index);
const void* Array_GetConst(const DynArray* array, size_t index);

void* Array_Back(DynArray* array);
const void* Array_BackConst(const DynArray* array);

bool Array_Insert(DynArray* array, size_t index, const void* value);
bool Array_RemoveAt(DynArray* array, size_t index);
bool Array_RemoveAtSwap(DynArray* array, size_t index);

void Array_Clear(DynArray* array);
void Array_Destroy(DynArray* array);


#endif
