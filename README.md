# BasilsTools

A lightweight modular C utility library focused on reusable data structures,
memory-safe containers, and game-development foundations.

Designed for:

- Raylib projects
- SDL projects
- ASCII engines
- Tile systems
- Simulation grids
- General-purpose C programming

---

# Features

Current modules include:

- Generic Dynamic Arrays
- Dynamic 2D Arrays
- Dynamic 3D Arrays
- Automatic memory resizing
- Contiguous cache-friendly layouts
- Safe insert/remove operations
- Copy and move semantics

---

# Project Structure

```txt
BasilsTools/
├─ include/
│  ├─ DynamicArray.h
│  ├─ DynamicArray2D.h
│  ├─ DynamicArray3D.h
│  ├─BGrid.h
│  └─ BTile.h
│
├─ src/
│  ├─ DynamicArray.c
│  ├─ DynamicArray2D.c
│  ├─ DynamicArray3D.c
│  ├─ BGrid.c
│  └─ BTile.c
├─ tests/
├─ CMakeLists.txt
└─ README.md
```

---

# Building

## Configure

```powershell
cmake -S . -B build
```

## Build

```powershell
cmake --build build
```

---

# Linking Into Another Project

```cmake
add_subdirectory(external/BasilsTools)

target_link_libraries(MyProject
    PRIVATE
        BasilsTools
)
```

---

# Including Headers

```c
#include "DynamicArray.h"
#include "DynamicArray2D.h"
#include "DynamicArray3D.h"
```

---

# Dynamic Array (1D)

Provides a generic resizable contiguous memory container similar to
`std::vector` in C++.

Supports:

- Automatic resizing
- Push/pop operations
- Insert/remove operations
- Indexed access
- Generic element storage
- Copy/move semantics

---

# DynArray Structure

```c
typedef struct DynArray
{
    void* data;

    size_t elementSize;

    size_t count;
    size_t capacity;

} DynArray;
```

---

# DynArray Functions

---

## Array_Init

Initializes a dynamic array.

### Parameters

| Parameter     | Description |
|---------------|-------------|
| array         | Array to initialize |
| elementSize   | Size of one element in bytes |

### Returns

`true` on success.

### Example

```c
DynArray numbers;

Array_Init(&numbers, sizeof(int));
```

---

## Array_Destroy

Destroys the array and frees all owned memory.

### Example

```c
Array_Destroy(&numbers);
```

---

## Array_Clear

Clears all elements without freeing allocated capacity.

### Example

```c
Array_Clear(&numbers);
```

---

## Array_PushBack

Appends an element to the end of the array.

Automatically resizes when capacity is exceeded.

### Example

```c
int value = 42;

Array_PushBack(&numbers, &value);
```

---

## Array_PopBack

Removes the last element.

### Example

```c
int value;

Array_PopBack(&numbers, &value);
```

---

## Array_Get

Returns a pointer to an element at an index.

### Example

```c
int* value =
    (int*)Array_Get(&numbers, 0);

printf("%d\n", *value);
```

---

## Array_Set

Copies data into an element slot.

### Example

```c
int value = 99;

Array_Set(&numbers, 0, &value);
```

---

## Array_Insert

Inserts an element at an index.

### Example

```c
int value = 123;

Array_Insert(&numbers, 1, &value);
```

---

## Array_RemoveAt

Removes an element while preserving order.

### Example

```c
Array_RemoveAt(&numbers, 2);
```

---

## Array_RemoveAtSwap

Removes an element by swapping with the last element.

Faster than `Array_RemoveAt`, but does not preserve order.

### Example

```c
Array_RemoveAtSwap(&numbers, 2);
```

---

## Array_Reserve

Reserves memory capacity.

### Example

```c
Array_Reserve(&numbers, 128);
```

---

## Array_Resize

Changes the element count of the array.

### Example

```c
Array_Resize(&numbers, 64);
```

---

## Array_ShrinkToFit

Shrinks allocated memory to exactly fit the current element count.

### Example

```c
Array_ShrinkToFit(&numbers);
```

---

# DynamicArray2D

Provides a contiguous dynamic 2D memory grid.

Useful for:

- Tilemaps
- ASCII engines
- Cellular automata
- Pathfinding
- Game boards

---

# DynArray2D Structure

```c
typedef struct DynArray2D
{
    DynArray buffer;

    size_t width;
    size_t height;

    size_t elementSize;

} DynArray2D;
```

---

# Example Usage

```c
DynArray2D grid;

Array2D_Init(&grid, 10, 10, sizeof(int));

int value = 7;

Array2D_Set(&grid, 2, 3, &value);

int* result =
    (int*)Array2D_Get(&grid, 2, 3);

printf("%d\n", *result);

Array2D_Destroy(&grid);
```

---

# DynamicArray2D Functions

- Array2D_Init
- Array2D_Destroy
- Array2D_Clear
- Array2D_Resize
- Array2D_Fill
- Array2D_Set
- Array2D_Get
- Array2D_IsInBounds
- Array2D_GetIndex
- Array2D_GetPosition
- Array2D_Count
- Array2D_Copy
- Array2D_Move

---

# DynamicArray3D

Provides a contiguous dynamic 3D memory grid.

Useful for:

- Voxel systems
- Chunk systems
- Layered tilemaps
- Simulation spaces
- Spatial partitioning

---

# DynArray3D Structure

```c
typedef struct DynArray3D
{
    DynArray buffer;

    size_t width;
    size_t height;
    size_t depth;

    size_t elementSize;

} DynArray3D;
```

---

# Example Usage

```c
DynArray3D world;

Array3D_Init(&world, 16, 16, 16, sizeof(int));

int tile = 1;

Array3D_Set(&world, 4, 2, 8, &tile);

int* result =
    (int*)Array3D_Get(&world, 4, 2, 8);

printf("%d\n", *result);

Array3D_Destroy(&world);
```

---

# DynamicArray3D Functions

- Array3D_Init
- Array3D_Destroy
- Array3D_Clear
- Array3D_Resize
- Array3D_Fill
- Array3D_Set
- Array3D_Get
- Array3D_IsInBounds
- Array3D_GetIndex
- Array3D_GetPosition
- Array3D_Count
- Array3D_Copy
- Array3D_Move

---

# Memory Ownership Rules

BasilsTools owns all internally allocated memory.

You must call:

```c
Array_Destroy()
Array2D_Destroy()
Array3D_Destroy()
```

when finished using containers.

---

# Design Goals

- Pure C
- Reusable
- Game-dev focused
- Cache-friendly memory layouts
- Expandable architecture
- Minimal dependencies
- Easy engine integration

---

# Future Plans

- Generic tile system
- Hash maps
- Arena allocators
- String utilities
- ECS containers
- Serialization systems
- Math utilities
- Grid projection helpers
- Raylib examples
- SDL examples

---

---

# Tile and Grid Tools

BasilsTools includes a lightweight tile/grid system built on top of `DynArray3D`.

The system is made of two main types:

- `BTile`
- `BGrid`

`BTile` represents one tile cell.
`BGrid` represents a 3D tile grid using width, height, and layers.

---

## Including Tile and Grid

```c
#include "BTile.h"
#include "BGrid.h"
