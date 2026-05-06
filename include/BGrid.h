#ifndef BGRID_H
#define BGRID_H

#include <stdbool.h>
#include <stddef.h>

#include "DynamicArray3D.h"
#include "BTile.h"

typedef struct BGrid
{
    size_t width;
    size_t height;
    size_t layers;

    DynArray3D tiles;
} BGrid;

bool BGrid_Init(BGrid* grid, size_t width, size_t height, size_t layers);
BGrid* BGrid_Create(size_t width, size_t height, size_t layers);

void BGrid_Clear(BGrid* grid);
void BGrid_Destroy(BGrid* grid);
void BGrid_Delete(BGrid* grid);

bool BGrid_IsInBounds(const BGrid* grid, size_t x, size_t y, size_t layer);

bool BGrid_SetTile(BGrid* grid, size_t x, size_t y, size_t layer, BTile tile);
bool BGrid_GetTile(const BGrid* grid, size_t x, size_t y, size_t layer, BTile* outTile);

BTile* BGrid_GetTilePtr(BGrid* grid, size_t x, size_t y, size_t layer);
const BTile* BGrid_GetTileConstPtr(const BGrid* grid, size_t x, size_t y, size_t layer);

bool BGrid_Fill(BGrid* grid, BTile tile);

size_t BGrid_GetWidth(const BGrid* grid);
size_t BGrid_GetHeight(const BGrid* grid);
size_t BGrid_GetLayers(const BGrid* grid);
size_t BGrid_GetTileCount(const BGrid* grid);

#endif
