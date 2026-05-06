#include "../include/DynamicArray.h"
#include "../include/DynamicArray2D.h"
#include "../include/DynamicArray3D.h"
#include <stdio.h>


static void PrintLayer(DynArray3D* array, size_t z)
{
    printf("Layer %zu:\n", z);

    for (size_t y = 0; y < array->height; y++)
    {
        for (size_t x = 0; x < array->width; x++)
        {
            int* value = (int*)Array3D_Get(array, x, y, z);
            printf("%d ", *value);
        }

        printf("\n");
    }

    printf("\n");
}

typedef struct TestPlayer
{
    int id;
    float health;
} TestPlayer;

static void PrintIntArray(DynArray* array)
{
    printf("count: %zu | capacity: %zu\n", array->count, array->capacity);

    for (size_t i = 0; i < array->count; i++)
    {
        int* value = (int*)Array_Get(array, i);
        printf("%d ", *value);
    }

    printf("\n\n");
}



static void PrintGrid(DynArray2D* grid)
{
    for (size_t y = 0; y < grid->height; y++)
    {
        for (size_t x = 0; x < grid->width; x++)
        {
            int* value = (int*)Array2D_Get(grid, x, y);
            printf("%d ", *value);
        }

        printf("\n");
    }

    printf("\n");
}


int main(void)
{
    DynArray numbers;

    if (!Array_Init(&numbers, sizeof(int)))
    {
        printf("Failed to initialize numbers array.\n");
        return 1;
    }

    printf("PushBack test:\n");
    for (int i = 0; i < 10; i++)
    {
        Array_PushBack(&numbers, &i);
    }
    PrintIntArray(&numbers);

    printf("Set index 3 to 999:\n");
    int newValue = 999;
    Array_Set(&numbers, 3, &newValue);
    PrintIntArray(&numbers);

    printf("Insert 555 at index 2:\n");
    int insertedValue = 555;
    Array_Insert(&numbers, 2, &insertedValue);
    PrintIntArray(&numbers);

    printf("RemoveAt index 4:\n");
    Array_RemoveAt(&numbers, 4);
    PrintIntArray(&numbers);

    printf("RemoveAtSwap index 1:\n");
    Array_RemoveAtSwap(&numbers, 1);
    PrintIntArray(&numbers);

    printf("Back test:\n");
    int* back = (int*)Array_Back(&numbers);
    if (back != NULL)
        printf("Back value: %d\n\n", *back);

    printf("PopBack test:\n");
    int poppedValue = 0;
    if (Array_PopBack(&numbers, &poppedValue))
        printf("Popped value: %d\n", poppedValue);
    PrintIntArray(&numbers);

    printf("Resize to 15:\n");
    Array_Resize(&numbers, 15);
    PrintIntArray(&numbers);

    printf("ShrinkToFit:\n");
    Array_ShrinkToFit(&numbers);
    PrintIntArray(&numbers);

    Array_Free(&numbers);

    printf("Struct array test:\n");

    DynArray players;
    Array_Init(&players, sizeof(TestPlayer));

    TestPlayer p1 = { 1, 100.0f };
    TestPlayer p2 = { 2, 75.5f };
    TestPlayer p3 = { 3, 42.0f };

    Array_PushBack(&players, &p1);
    Array_PushBack(&players, &p2);
    Array_PushBack(&players, &p3);

    for (size_t i = 0; i < players.count; i++)
    {
        TestPlayer* player = (TestPlayer*)Array_Get(&players, i);
        printf("Player %d | Health: %.2f\n", player->id, player->health);
    }

    Array_Free(&players);

    DynArray2D grid;

    if (!Array2D_Init(&grid, 3, 3, sizeof(int)))
    {
        printf("Failed to initialize grid.\n");
        return 1;
    }

    int fillValue = 1;
    Array2D_Fill(&grid, &fillValue);

    int center = 99;
    Array2D_Set(&grid, 1, 1, &center);

    printf("Original 3x3 grid:\n");
    PrintGrid(&grid);

    Array2D_Resize(&grid, 5, 4);

    printf("Resized 5x4 grid:\n");
    PrintGrid(&grid);

    size_t index = 0;
    if (Array2D_GetIndex(&grid, 2, 1, &index))
    {
        printf("Index of position (2, 1): %zu\n", index);
    }

    size_t x = 0;
    size_t y = 0;

    if (Array2D_GetPosition(&grid, index, &x, &y))
    {
        printf("Position of index %zu: (%zu, %zu)\n", index, x, y);
    }

    Array2D_Free(&grid);

    DynArray3D volume;

    if (!Array3D_Init(&volume, 3, 3, 2, sizeof(int)))
    {
        printf("Failed to initialize 3D array.\n");
        return 1;
    }

    int fillValue3D = 1;
    Array3D_Fill(&volume, &fillValue3D);

    int specialValue = 99;
    Array3D_Set(&volume, 1, 1, 0, &specialValue);

    int deeperValue = 77;
    Array3D_Set(&volume, 2, 2, 1, &deeperValue);

    printf("Original 3x3x2 volume:\n");
    PrintLayer(&volume, 0);
    PrintLayer(&volume, 1);

    Array3D_Resize(&volume, 4, 4, 3);

    printf("Resized 4x4x3 volume:\n");
    PrintLayer(&volume, 0);
    PrintLayer(&volume, 1);
    PrintLayer(&volume, 2);

    size_t index3D = 0;

    if (Array3D_GetIndex(&volume, 2, 2, 1, &index))
    {
        printf("Index of position (2, 2, 1): %zu\n", index3D);
    }

    size_t x3D = 0;
    size_t y3D = 0;
    size_t z3D = 0;

    if (Array3D_GetPosition(&volume, index3D, &x3D, &y3D, &z3D))
    {
        printf("Position of index %zu: (%zu, %zu, %zu)\n", index3D, x3D, y3D, z3D);
    }

    Array3D_Free(&volume);


    return 0;
}
