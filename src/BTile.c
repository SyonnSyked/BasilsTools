#include "../include/BTile.h"

BTile BTile_Create(int id)
{
    BTile tile;

    tile.id = id;
    tile.flags = BTILE_FLAG_NONE;
    tile.data = 0;

    return tile;
}

BTile BTile_CreateWithData(int id, uint32_t flags, void* data)
{
    BTile tile;

    tile.id = id;
    tile.flags = flags;
    tile.data = data;

    return tile;
}

BTile BTile_Empty(void)
{
    BTile tile;

    tile.id = 0;
    tile.flags = BTILE_FLAG_NONE;
    tile.data = 0;

    return tile;
}

bool BTile_HasFlag(const BTile* tile, uint32_t flag)
{
    if (tile == 0)
        return false;

    return (tile->flags & flag) != 0;
}

void BTile_AddFlag(BTile* tile, uint32_t flag)
{
    if (tile == 0)
        return;

    tile->flags |= flag;
}

void BTile_RemoveFlag(BTile* tile, uint32_t flag)
{
    if (tile == 0)
        return;

    tile->flags &= ~flag;
}

void BTile_SetFlags(BTile* tile, uint32_t flags)
{
    if (tile == 0)
        return;

    tile->flags = flags;
}
