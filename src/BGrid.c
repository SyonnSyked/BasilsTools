#include "../include/BGrid.h"

#include <stdlib.h>

bool BGrid_Init(BGrid* grid, size_t width, size_t height, size_t layers)
{
    if (grid == 0)
        return false;

    if (width == 0 || height == 0 || layers == 0)
        return false;

    if (!Array3D_Init(&grid->tiles, width, height, layers, sizeof(BTile)))
        return false;

    grid->width = width;
    grid->height = height;
    grid->layers = layers;

    BTile emptyTile = BTile_Empty();

    if (!Array3D_Fill(&grid->tiles, &emptyTile))
    {
        Array3D_Destroy(&grid->tiles);

        grid->width = 0;
        grid->height = 0;
        grid->layers = 0;

        return false;
    }

    return true;
}

BGrid* BGrid_Create(size_t width, size_t height, size_t layers)
{
    BGrid* grid = malloc(sizeof(BGrid));

    if (grid == 0)
        return 0;

    if (!BGrid_Init(grid, width, height, layers))
    {
        free(grid);
        return 0;
    }

    return grid;
}

void BGrid_Clear(BGrid* grid)
{
    if (grid == 0)
        return;

    BTile emptyTile = BTile_Empty();

    Array3D_Fill(&grid->tiles, &emptyTile);
}

void BGrid_Destroy(BGrid* grid)
{
    if (grid == 0)
        return;

    Array3D_Destroy(&grid->tiles);

    grid->width = 0;
    grid->height = 0;
    grid->layers = 0;
}

void BGrid_Delete(BGrid* grid)
{
    if (grid == 0)
        return;

    BGrid_Destroy(grid);
    free(grid);
}

bool BGrid_IsInBounds(const BGrid* grid, size_t x, size_t y, size_t layer)
{
    if (grid == 0)
        return false;

    return x < grid->width &&
           y < grid->height &&
           layer < grid->layers;
}

bool BGrid_SetTile(BGrid* grid, size_t x, size_t y, size_t layer, BTile tile)
{
    if (grid == 0)
        return false;

    if (!BGrid_IsInBounds(grid, x, y, layer))
        return false;

    return Array3D_Set(&grid->tiles, x, y, layer, &tile);
}

bool BGrid_GetTile(const BGrid* grid, size_t x, size_t y, size_t layer, BTile* outTile)
{
    if (grid == 0 || outTile == 0)
        return false;

    if (!BGrid_IsInBounds(grid, x, y, layer))
        return false;

    const BTile* tile = Array3D_GetConst(&grid->tiles, x, y, layer);

    if (tile == 0)
        return false;

    *outTile = *tile;

    return true;
}

BTile* BGrid_GetTilePtr(BGrid* grid, size_t x, size_t y, size_t layer)
{
    if (grid == 0)
        return 0;

    if (!BGrid_IsInBounds(grid, x, y, layer))
        return 0;

    return Array3D_Get(&grid->tiles, x, y, layer);
}

const BTile* BGrid_GetTileConstPtr(const BGrid* grid, size_t x, size_t y, size_t layer)
{
    if (grid == 0)
        return 0;

    if (!BGrid_IsInBounds(grid, x, y, layer))
        return 0;

    return Array3D_GetConst(&grid->tiles, x, y, layer);
}

bool BGrid_Fill(BGrid* grid, BTile tile)
{
    if (grid == 0)
        return false;

    return Array3D_Fill(&grid->tiles, &tile);
}

size_t BGrid_GetWidth(const BGrid* grid)
{
    if (grid == 0)
        return 0;

    return grid->width;
}

size_t BGrid_GetHeight(const BGrid* grid)
{
    if (grid == 0)
        return 0;

    return grid->height;
}

size_t BGrid_GetLayers(const BGrid* grid)
{
    if (grid == 0)
        return 0;

    return grid->layers;
}

size_t BGrid_GetTileCount(const BGrid* grid)
{
    if (grid == 0)
        return 0;

    return grid->width * grid->height * grid->layers;
}

