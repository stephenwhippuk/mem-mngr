# MemAlloc Module Documentation

## Overview
`MemAlloc` is a memory allocator class that manages fixed-size memory blocks. It is responsible for allocating, deallocating, and tracking memory blocks by unique IDs. `MemAlloc` is used by higher-level memory contexts (such as `PagedContext`) to provide efficient and safe memory management.

## Types
- `word_t`: 16-bit unsigned integer (from `vtypes.h`)
- `dword_t`: 32-bit unsigned integer (from `vtypes.h`)
- `block_t`: `std::vector<word_t>` (a block of memory)

## Construction
```
MemAlloc(dword_t blockSize, dword_t maxBlocks);
```
- **blockSize**: Size of each block in words (16 bits per word)
- **maxBlocks**: Maximum number of blocks that can be allocated
- Throws `std::invalid_argument` if the total memory exceeds 4.3GB

## Methods

### allocate
```
int allocate(word_t id, word_t words);
```
- **Description:** Allocates a block with the given ID and size (in words). Returns the block ID on success, or -1 on error (size too large, max blocks reached, or ID in use).

### deallocate
```
void deallocate(word_t blockId);
```
- **Description:** Deallocates the block with the given ID.

### getBlock
```
std::shared_ptr<block_t> getBlock(word_t blockId);
```
- **Description:** Returns a shared pointer to the block with the given ID, or `nullptr` if not found.

## Error Handling
- Throws `std::invalid_argument` if total allocation exceeds 4.3GB in the constructor.
- `allocate` returns -1 for errors (oversize, max blocks, duplicate ID).

## Usage Example
```cpp
#include "memalloc.h"
MemAlloc allocator(16, 10);
int blockId = allocator.allocate(1, 8);
auto block = allocator.getBlock(blockId);
allocator.deallocate(blockId);
```

## Test Coverage
Unit tests for MemAlloc are in `tests/test_memalloc.cpp` and `tests/test_mem_classes.cpp`, covering:
- Allocation and deallocation
- Max blocks and duplicate ID errors
- Block retrieval and lifecycle
