#include "../include/DynamicArray.h"
#include "../include/DynamicArray2D.h"
#include "../include/DynamicArray3D.h"
#include "../include/BTile.h"
#include "../include/BGrid.h"
#include <stdio.h>

static void PrintBGridVisual(BGrid* grid, size_t layer)
{
    printf("Visual BGrid Layer %zu:\n\n", layer);

    for (size_t y = 0; y < BGrid_GetHeight(grid); y++)
    {
        for (size_t x = 0; x < BGrid_GetWidth(grid); x++)
            printf("+---");

        printf("+\n");

        for (size_t x = 0; x < BGrid_GetWidth(grid); x++)
        {
            BTile tile;

            if (BGrid_GetTile(grid, x, y, layer, &tile))
                printf("| %d ", tile.id);
            else
                printf("| ? ");
        }

        printf("|\n");
    }

    for (size_t x = 0; x < BGrid_GetWidth(grid); x++)
        printf("+---");

    printf("+\n\n");
}

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


static void PrintBGrid(BGrid* grid, size_t layer)
{
    printf("BGrid Layer %zu:\n", layer);

    for (size_t y = 0; y < BGrid_GetHeight(grid); y++)
    {
        for (size_t x = 0; x < BGrid_GetWidth(grid); x++)
        {
            BTile tile;

            if (BGrid_GetTile(grid, x, y, layer, &tile))
                printf("%d ", tile.id);
            else
                printf("? ");
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

    if (Array3D_GetIndex(&volume, 2, 2, 1, &index3D))
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

    printf("BTile and BGrid test:\n");

    BGrid tileGrid;

    if (!BGrid_Init(&tileGrid, 5, 4, 2))
    {
        printf("Failed to initialize BGrid.\n");
        return 1;
    }

    BTile grass = BTile_Create(1);
    BTile wall = BTile_CreateWithData(2, BTILE_FLAG_SOLID | BTILE_FLAG_BLOCKS_LIGHT, NULL);
    BTile water = BTile_CreateWithData(3, BTILE_FLAG_VISIBLE, NULL);

    BGrid_Fill(&tileGrid, grass);

    BGrid_SetTile(&tileGrid, 2, 1, 0, wall);
    BGrid_SetTile(&tileGrid, 3, 2, 0, water);
    BGrid_SetTile(&tileGrid, 1, 1, 1, wall);

    PrintBGridVisual(&tileGrid, 0);
    PrintBGridVisual(&tileGrid, 1);

    PrintBGrid(&tileGrid, 0);
    PrintBGrid(&tileGrid, 1);

    BTile checkedTile;

    if (BGrid_GetTile(&tileGrid, 2, 1, 0, &checkedTile))
    {
        printf("Tile at (2, 1, 0): id=%d flags=%u\n", checkedTile.id, checkedTile.flags);

        if (BTile_HasFlag(&checkedTile, BTILE_FLAG_SOLID))
            printf("This tile is solid.\n");

        if (BTile_HasFlag(&checkedTile, BTILE_FLAG_BLOCKS_LIGHT))
            printf("This tile blocks light.\n");
    }

    printf("\nTesting out-of-bounds check:\n");

    if (!BGrid_IsInBounds(&tileGrid, 99, 99, 0))
        printf("(99, 99, 0) is correctly detected as out of bounds.\n");

    BGrid_Clear(&tileGrid);

    printf("\nAfter BGrid_Clear:\n");
    PrintBGrid(&tileGrid, 0);

    BGrid_Destroy(&tileGrid);

    printf("\n==============================\n");
    printf("FULL MEMORY MANAGEMENT CHECKS\n");
    printf("==============================\n\n");

    /*
        MEMORY TEST 1:
        Stack-allocated BGrid init/destroy.
    */
    printf("[1] Stack BGrid Init/Destroy:\n");

    BGrid memoryGrid;

    if (BGrid_Init(&memoryGrid, 3, 3, 2))
    {
        printf("PASS: BGrid_Init succeeded.\n");

        BTile testTile = BTile_CreateWithData(7, BTILE_FLAG_SOLID, NULL);

        if (BGrid_SetTile(&memoryGrid, 1, 1, 0, testTile))
            printf("PASS: BGrid_SetTile succeeded.\n");
        else
            printf("FAIL: BGrid_SetTile failed.\n");

        BGrid_Destroy(&memoryGrid);

        if (memoryGrid.width == 0 &&
            memoryGrid.height == 0 &&
            memoryGrid.layers == 0)
        {
            printf("PASS: BGrid_Destroy reset dimensions.\n");
        }
        else
        {
            printf("FAIL: BGrid_Destroy did not reset dimensions.\n");
        }
    }
    else
    {
        printf("FAIL: BGrid_Init failed.\n");
    }

    printf("\n");

    /*
        MEMORY TEST 2:
        Heap-allocated BGrid create/delete.
    */
    printf("[2] Heap BGrid Create/Delete:\n");

    BGrid* heapGrid = BGrid_Create(4, 4, 3);

    if (heapGrid != NULL)
    {
        printf("PASS: BGrid_Create succeeded.\n");

        BTile heapTile = BTile_CreateWithData(9, BTILE_FLAG_VISIBLE, NULL);

        if (BGrid_SetTile(heapGrid, 2, 2, 1, heapTile))
            printf("PASS: Heap grid tile set succeeded.\n");
        else
            printf("FAIL: Heap grid tile set failed.\n");

        BGrid_Delete(heapGrid);
        heapGrid = NULL;

        if (heapGrid == NULL)
            printf("PASS: Heap pointer manually nulled after BGrid_Delete.\n");
    }
    else
    {
        printf("FAIL: BGrid_Create failed.\n");
    }

    printf("\n");

    /*
        MEMORY TEST 3:
        Invalid grid dimensions.
    */
    printf("[3] Invalid Dimension Protection:\n");

    BGrid invalidGrid;

    if (!BGrid_Init(&invalidGrid, 0, 5, 1))
        printf("PASS: Rejected width of 0.\n");
    else
    {
        printf("FAIL: Accepted invalid width.\n");
        BGrid_Destroy(&invalidGrid);
    }

    if (!BGrid_Init(&invalidGrid, 5, 0, 1))
        printf("PASS: Rejected height of 0.\n");
    else
    {
        printf("FAIL: Accepted invalid height.\n");
        BGrid_Destroy(&invalidGrid);
    }

    if (!BGrid_Init(&invalidGrid, 5, 5, 0))
        printf("PASS: Rejected layer count of 0.\n");
    else
    {
        printf("FAIL: Accepted invalid layer count.\n");
        BGrid_Destroy(&invalidGrid);
    }

    printf("\n");

    /*
        MEMORY TEST 4:
        Out-of-bounds access.
    */
    printf("[4] Out-of-Bounds Access Protection:\n");

    BGrid boundsGrid;

    if (BGrid_Init(&boundsGrid, 2, 2, 1))
    {
        BTile boundsTile = BTile_Create(5);
        BTile outTile;

        if (!BGrid_SetTile(&boundsGrid, 99, 0, 0, boundsTile))
            printf("PASS: Rejected out-of-bounds X set.\n");
        else
            printf("FAIL: Accepted out-of-bounds X set.\n");

        if (!BGrid_SetTile(&boundsGrid, 0, 99, 0, boundsTile))
            printf("PASS: Rejected out-of-bounds Y set.\n");
        else
            printf("FAIL: Accepted out-of-bounds Y set.\n");

        if (!BGrid_SetTile(&boundsGrid, 0, 0, 99, boundsTile))
            printf("PASS: Rejected out-of-bounds layer set.\n");
        else
            printf("FAIL: Accepted out-of-bounds layer set.\n");

        if (!BGrid_GetTile(&boundsGrid, 99, 0, 0, &outTile))
            printf("PASS: Rejected out-of-bounds X get.\n");
        else
            printf("FAIL: Accepted out-of-bounds X get.\n");

        BGrid_Destroy(&boundsGrid);
    }
    else
    {
        printf("FAIL: Could not initialize boundsGrid.\n");
    }

    printf("\n");

    /*
        MEMORY TEST 5:
        NULL pointer safety.
    */
    printf("[5] NULL Pointer Safety:\n");

    if (!BGrid_Init(NULL, 2, 2, 1))
        printf("PASS: BGrid_Init rejects NULL grid.\n");
    else
        printf("FAIL: BGrid_Init accepted NULL grid.\n");

    BGrid_Destroy(NULL);
    BGrid_Delete(NULL);
    BGrid_Clear(NULL);

    if (!BGrid_IsInBounds(NULL, 0, 0, 0))
        printf("PASS: BGrid_IsInBounds rejects NULL grid.\n");
    else
        printf("FAIL: BGrid_IsInBounds accepted NULL grid.\n");

    if (!BGrid_SetTile(NULL, 0, 0, 0, BTile_Create(1)))
        printf("PASS: BGrid_SetTile rejects NULL grid.\n");
    else
        printf("FAIL: BGrid_SetTile accepted NULL grid.\n");

    if (!BGrid_GetTile(NULL, 0, 0, 0, NULL))
        printf("PASS: BGrid_GetTile rejects NULL grid/outTile.\n");
    else
        printf("FAIL: BGrid_GetTile accepted NULL arguments.\n");

    if (BGrid_GetTilePtr(NULL, 0, 0, 0) == NULL)
        printf("PASS: BGrid_GetTilePtr rejects NULL grid.\n");
    else
        printf("FAIL: BGrid_GetTilePtr accepted NULL grid.\n");

    printf("\n");

    /*
        MEMORY TEST 6:
        Clear should preserve allocation but reset tile contents.
    */
    printf("[6] Clear Behavior:\n");

    BGrid clearGrid;

    if (BGrid_Init(&clearGrid, 3, 3, 1))
    {
        BTile specialTile = BTile_CreateWithData(44, BTILE_FLAG_SOLID, NULL);
        BTile readTile;

        BGrid_SetTile(&clearGrid, 1, 1, 0, specialTile);

        if (BGrid_GetTile(&clearGrid, 1, 1, 0, &readTile) && readTile.id == 44)
            printf("PASS: Tile was set before clear.\n");
        else
            printf("FAIL: Tile was not set before clear.\n");

        BGrid_Clear(&clearGrid);

        if (BGrid_GetTile(&clearGrid, 1, 1, 0, &readTile) && readTile.id == 0)
            printf("PASS: BGrid_Clear reset tile to empty.\n");
        else
            printf("FAIL: BGrid_Clear did not reset tile to empty.\n");

        if (clearGrid.width == 3 &&
            clearGrid.height == 3 &&
            clearGrid.layers == 1)
        {
            printf("PASS: BGrid_Clear preserved grid dimensions.\n");
        }
        else
        {
            printf("FAIL: BGrid_Clear changed grid dimensions.\n");
        }

        BGrid_Destroy(&clearGrid);
    }
    else
    {
        printf("FAIL: Could not initialize clearGrid.\n");
    }

    printf("\n");

    /*
        MEMORY TEST 7:
        Pointer access validity.
    */
    printf("[7] Tile Pointer Access:\n");

    BGrid ptrGrid;

    if (BGrid_Init(&ptrGrid, 2, 2, 1))
    {
        BTile* tilePtr = BGrid_GetTilePtr(&ptrGrid, 1, 1, 0);

        if (tilePtr != NULL)
        {
            printf("PASS: BGrid_GetTilePtr returned valid pointer.\n");

            tilePtr->id = 88;
            tilePtr->flags = BTILE_FLAG_INTERACTIVE;

            BTile checkPtrTile;

            if (BGrid_GetTile(&ptrGrid, 1, 1, 0, &checkPtrTile) &&
                checkPtrTile.id == 88 &&
                BTile_HasFlag(&checkPtrTile, BTILE_FLAG_INTERACTIVE))
            {
                printf("PASS: Direct pointer modification affected grid storage.\n");
            }
            else
            {
                printf("FAIL: Direct pointer modification did not affect grid storage.\n");
            }
        }
        else
        {
            printf("FAIL: BGrid_GetTilePtr returned NULL for valid position.\n");
        }

        if (BGrid_GetTilePtr(&ptrGrid, 9, 9, 0) == NULL)
            printf("PASS: BGrid_GetTilePtr rejected invalid position.\n");
        else
            printf("FAIL: BGrid_GetTilePtr accepted invalid position.\n");

        BGrid_Destroy(&ptrGrid);
    }
    else
    {
        printf("FAIL: Could not initialize ptrGrid.\n");
    }

    printf("\n");

    /*
        MEMORY TEST 8:
        Repeated create/destroy cycle.
    */
    printf("[8] Repeated Create/Destroy Stress Test:\n");

    int stressPassed = 1;

    for (int i = 0; i < 1000; i++)
    {
        BGrid* stressGrid = BGrid_Create(10, 10, 3);

        if (stressGrid == NULL)
        {
            stressPassed = 0;
            printf("FAIL: BGrid_Create failed on iteration %d.\n", i);
            break;
        }

        BTile stressTile = BTile_CreateWithData(i, BTILE_FLAG_VISIBLE, NULL);

        if (!BGrid_SetTile(stressGrid, 5, 5, 1, stressTile))
        {
            stressPassed = 0;
            printf("FAIL: BGrid_SetTile failed on iteration %d.\n", i);
            BGrid_Delete(stressGrid);
            break;
        }

        BGrid_Delete(stressGrid);
    }

    if (stressPassed)
        printf("PASS: 1000 create/set/delete cycles completed.\n");

    printf("\n");

    /*
        MEMORY TEST 9:
        User data pointer storage.
    */
    printf("[9] Tile void* Data Pointer Storage:\n");

    int customData = 12345;

    BTile dataTile = BTile_CreateWithData(12, BTILE_FLAG_VISIBLE, &customData);

    if (dataTile.data == &customData)
        printf("PASS: BTile stored external data pointer correctly.\n");
    else
        printf("FAIL: BTile failed to store external data pointer.\n");

    if (*(int*)dataTile.data == 12345)
        printf("PASS: BTile data pointer dereferenced correctly.\n");
    else
        printf("FAIL: BTile data pointer dereference failed.\n");

    printf("\n");

    /*
        MEMORY TEST 10:
        BTile flag safety.
    */
    printf("[10] BTile Flag Operations:\n");

    BTile flagTile = BTile_Create(20);

    BTile_AddFlag(&flagTile, BTILE_FLAG_SOLID);
    BTile_AddFlag(&flagTile, BTILE_FLAG_BLOCKS_LIGHT);

    if (BTile_HasFlag(&flagTile, BTILE_FLAG_SOLID))
        printf("PASS: Added SOLID flag.\n");
    else
        printf("FAIL: Failed to add SOLID flag.\n");

    if (BTile_HasFlag(&flagTile, BTILE_FLAG_BLOCKS_LIGHT))
        printf("PASS: Added BLOCKS_LIGHT flag.\n");
    else
        printf("FAIL: Failed to add BLOCKS_LIGHT flag.\n");

    BTile_RemoveFlag(&flagTile, BTILE_FLAG_SOLID);

    if (!BTile_HasFlag(&flagTile, BTILE_FLAG_SOLID))
        printf("PASS: Removed SOLID flag.\n");
    else
        printf("FAIL: Failed to remove SOLID flag.\n");

    BTile_SetFlags(&flagTile, BTILE_FLAG_VISIBLE | BTILE_FLAG_INTERACTIVE);

    if (BTile_HasFlag(&flagTile, BTILE_FLAG_VISIBLE) &&
        BTile_HasFlag(&flagTile, BTILE_FLAG_INTERACTIVE))
    {
        printf("PASS: BTile_SetFlags worked.\n");
    }
    else
    {
        printf("FAIL: BTile_SetFlags failed.\n");
    }

    BTile_AddFlag(NULL, BTILE_FLAG_SOLID);
    BTile_RemoveFlag(NULL, BTILE_FLAG_SOLID);
    BTile_SetFlags(NULL, BTILE_FLAG_SOLID);

    if (!BTile_HasFlag(NULL, BTILE_FLAG_SOLID))
        printf("PASS: BTile flag functions handle NULL safely.\n");
    else
        printf("FAIL: BTile_HasFlag returned true for NULL.\n");

    printf("\n==============================\n");
    printf("MEMORY MANAGEMENT CHECKS DONE\n");
    printf("==============================\n\n");

    return 0;
}
