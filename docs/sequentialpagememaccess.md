# SequentialPageMemAccess Documentation

## Overview
`SequentialPageMemAccess` provides stream-like, sequential access to memory managed by a `SequentialPageContext`. It maintains a current page and offset, allowing reading and writing of 8-bit units or 16-bit chunks, and supports jumping to arbitrary page/offset locations. This accessor is designed for scenarios such as code execution or sequential data processing.

## Types
- `unit_t`/`byte_t`: 8-bit unsigned integer (from `vtypes.h`)
- `chunk_t`: 16-bit unsigned integer (from `vtypes.h`)
- `word_t`: 16-bit unsigned integer (from `vtypes.h`)
- `SequentialPageContext`: The owning context (from `context.h`)

## Construction
```
SequentialPageMemAccess(SequentialPageContext& context, word_t pageSize);
```
- **context**: Reference to the owning `SequentialPageContext`.
- **pageSize**: Size of each page in words.

## Methods

### getUnit
```
unit_t getUnit() const;
```
- **Description:** Returns the 8-bit unit at the current offset. Throws `std::out_of_range` if the offset is out of bounds.

### setUnit
```
void setUnit(unit_t value);
```
- **Description:** Sets the 8-bit unit at the current offset. Throws `std::out_of_range` if the offset is out of bounds.

### getChunk
```
chunk_t getChunk() const;
```
- **Description:** Returns the 16-bit chunk at the current offset (must be aligned to a chunk boundary). Throws `std::out_of_range` if the offset is out of bounds, or `std::invalid_argument` if not aligned.

### setChunk
```
void setChunk(chunk_t value);
```
- **Description:** Sets the 16-bit chunk at the current offset (must be aligned to a chunk boundary). Throws `std::out_of_range` if the offset is out of bounds, or `std::invalid_argument` if not aligned.

### jumpTo
```
void jumpTo(word_t pageIndex, word_t offset);
```
- **Description:** Moves the accessor to the specified page and offset.

## Error Handling
- All access methods throw `std::out_of_range` for out-of-bounds access.
- `getChunk` and `setChunk` throw `std::invalid_argument` if the offset is not aligned to a chunk boundary (must be even).

## Usage Example
```cpp
#include "memaccess.h"
SequentialPageContext ctx(...);
SequentialPageMemAccess seqAccess(ctx, ...);
seqAccess.setUnit(0x42);
unit_t u = seqAccess.getUnit();
seqAccess.jumpTo(1, 0);
seqAccess.setChunk(0xABCD);
```

## Test Coverage
Comprehensive unit and integration tests for `SequentialPageMemAccess` are in `tests/test_mem_classes.cpp`, covering:
- Sequential unit and chunk access
- Out-of-range and misaligned access
- Page/offset jumping
- Read/write correctness
