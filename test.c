#include "include/DynamicArray.h"
#include <stdio.h>

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

    return 0;
}
