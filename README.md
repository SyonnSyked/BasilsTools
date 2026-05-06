# C Tools Library

A lightweight C utility library including:

- Dynamic Array (generic)
- 2D and 3D array wrappers
- Memory-safe operations (insert, remove, resize, etc.)

## Build

```bash
cmake -S . -B build
cmake --build build




# BasilsTools

A lightweight modular C utility library focused on reusable data structures and game-development foundations.

Currently includes:

* Dynamic 1D Arrays
* Dynamic 2D Arrays
* Dynamic 3D Arrays
* Generic memory-safe resizing systems
* Expandable utility architecture

Designed for:

* Raylib projects
* SDL projects
* ASCII engines
* Tile systems
* Simulation grids
* General-purpose C programming

---

# Building

```powershell
mkdir build
cd build

cmake ..
cmake --build .
```

---

# Project Structure

```txt
BasilsTools/
├─ include/
├─ src/
├─ tests/
├─ build/
├─ CMakeLists.txt
└─ README.md
```

---

# Including BasilsTools

```c
#include <BasilsTools/DynamicArray.h>
#include <BasilsTools/DynamicArray2D.h>
#include <BasilsTools/DynamicArray3D.h>
```

---

# DynamicArray (1D)

## Purpose

Provides a resizable contiguous memory array similar to `std::vector` in C++.

Supports:

* automatic resizing
* indexed access
* push/pop operations
* generic element storage
* contiguous memory layout

---

# DynamicArray Structure

```c
typedef struct DynamicArray
{
    void* data;
    size_t elementSize;
    size_t size;
    size_t capacity;
} DynamicArray;
```

---

# Functions

---

## DynArray_Create

### Description

Creates a new dynamic array.

### Parameters

| Parameter       | Description                  |
| --------------- | ---------------------------- |
| elementSize     | Size of one element in bytes |
| initialCapacity | Starting capacity            |

### Returns

Initialized `DynamicArray`

### Example

```c
DynamicArray numbers =
    DynArray_Create(sizeof(int), 10);
```

---

## DynArray_Destroy

### Description

Frees all memory owned by the array.

### Parameters

| Parameter | Description      |
| --------- | ---------------- |
| array     | Array to destroy |

### Example

```c
DynArray_Destroy(&numbers);
```

---

## DynArray_PushBack

### Description

Appends an element to the end of the array.

Automatically resizes when capacity is exceeded.

### Parameters

| Parameter | Description             |
| --------- | ----------------------- |
| array     | Target array            |
| element   | Pointer to element data |

### Example

```c
int value = 42;

DynArray_PushBack(&numbers, &value);
```

---

## DynArray_Get

### Description

Returns a pointer to an element at the given index.

### Parameters

| Parameter | Description   |
| --------- | ------------- |
| array     | Target array  |
| index     | Element index |

### Returns

Pointer to the element.

### Example

```c
int* value =
    (int*)DynArray_Get(&numbers, 0);

printf("%d\n", *value);
```

---

## DynArray_Set

### Description

Copies data into an element slot.

### Example

```c
int value = 99;

DynArray_Set(&numbers, 0, &value);
```

---

## DynArray_Resize

### Description

Resizes the internal storage capacity.

Typically handled automatically.

### Example

```c
DynArray_Resize(&numbers, 128);
```

---

# DynamicArray2D

## Purpose

Provides a dynamic 2D grid.

Useful for:

* tilemaps
* ASCII engines
* cellular automata
* pathfinding
* game boards

---

# DynamicArray2D Structure

```c
typedef struct DynamicArray2D
{
    void* data;

    size_t elementSize;

    size_t width;
    size_t height;

} DynamicArray2D;
```

---

# Example Usage

```c
DynamicArray2D grid =
    DynArray2D_Create(sizeof(int), 10, 10);

int value = 7;

DynArray2D_Set(&grid, 2, 3, &value);

int* result =
    (int*)DynArray2D_Get(&grid, 2, 3);

printf("%d\n", *result);
```

---

# DynamicArray3D

## Purpose

Provides a dynamic 3D memory grid.

Useful for:

* voxel systems
* chunk systems
* layered tilemaps
* simulation spaces
* ECS spatial partitions

---

# Example Usage

```c
DynamicArray3D world =
    DynArray3D_Create(sizeof(int), 16, 16, 16);

int tile = 1;

DynArray3D_Set(&world, 4, 2, 8, &tile);

int* result =
    (int*)DynArray3D_Get(&world, 4, 2, 8);
```

---

# Memory Ownership Rules

BasilsTools owns all internally allocated memory.

You must call:

```c
DynArray_Destroy()
DynArray2D_Destroy()
DynArray3D_Destroy()
```

when finished using containers.

---

# Design Goals

* pure C
* reusable
* game-dev focused
* cache-friendly layouts
* expandable architecture
* minimal dependencies
* easy integration into engines

---

# Future Plans

* Generic Tile system
* Hash maps
* Arena allocators
* String utilities
* ECS containers
* Spatial partitioning
* Serialization systems
* Math utilities
* Grid projection helpers
* Raylib integration examples

---

# Example Linking in Another Project

```cmake
add_subdirectory(external/BasilsTools)

target_link_libraries(MyGame
    PRIVATE
        BasilsTools
)
```


