#ifndef BTILE_H
#define BTILE_H

#include <stdbool.h>
#include <stdint.h>

typedef enum BTileFlags
{
    BTILE_FLAG_NONE         = 0,
    BTILE_FLAG_SOLID        = 1 << 0,
    BTILE_FLAG_VISIBLE      = 1 << 1,
    BTILE_FLAG_INTERACTIVE  = 1 << 2,
    BTILE_FLAG_DESTRUCTIBLE = 1 << 3,
    BTILE_FLAG_BLOCKS_LIGHT = 1 << 4
} BTileFlags;

typedef struct BTile
{
    int id;

    uint32_t flags;

    void* data;
} BTile;

BTile BTile_Create(int id);
BTile BTile_CreateWithData(int id, uint32_t flags, void* data);
BTile BTile_Empty(void);

bool BTile_HasFlag(const BTile* tile, uint32_t flag);
void BTile_AddFlag(BTile* tile, uint32_t flag);
void BTile_RemoveFlag(BTile* tile, uint32_t flag);
void BTile_SetFlags(BTile* tile, uint32_t flags);

#endif
