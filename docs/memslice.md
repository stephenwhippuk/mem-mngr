# MemSlice Module Documentation

## Overview
`MemSlice` is a class that provides fine-grained access to a memory region represented as a vector of 16-bit words (chunks). It allows reading and writing individual 8-bit units (bytes) or entire 16-bit chunks, with bounds and alignment checking. `MemSlice` is a key component for memory access in the memory manager experiment.

## Types
- `chunk_t`: 16-bit unsigned integer (from `vtypes.h`)
- `unit_t`/`byte_t`: 8-bit unsigned integer (from `vtypes.h`)
- `index_t`: Index type for addressing units/chunks (from `vtypes.h`)

## Construction
```
MemSlice(std::shared_ptr<std::vector<chunk_t>> storage);
```
- **storage**: Shared pointer to a vector of 16-bit words representing the memory region.

## Methods

### getUnit
```
unit_t getUnit(index_t index) const;
```
- **Description:** Returns the 8-bit unit at the given index. Throws `std::out_of_range` if the index is out of bounds.

### setUnit
```
void setUnit(index_t index, unit_t value);
```
- **Description:** Sets the 8-bit unit at the given index. Throws `std::out_of_range` if the index is out of bounds.

### getChunk
```
chunk_t getChunk(index_t index) const;
```
- **Description:** Returns the 16-bit chunk at the given (even) index. Throws `std::out_of_range` if the index is out of bounds, or `std::invalid_argument` if the index is not aligned to a chunk boundary.

### setChunk
```
void setChunk(index_t index, chunk_t value);
```
- **Description:** Sets the 16-bit chunk at the given (even) index. Throws `std::out_of_range` if the index is out of bounds, or `std::invalid_argument` if the index is not aligned to a chunk boundary.

## Error Handling
- All access methods throw `std::out_of_range` for out-of-bounds access.
- `getChunk` and `setChunk` throw `std::invalid_argument` if the index is not aligned to a chunk boundary (must be even).

## Usage Example
```cpp
#include "memaccess.h"
auto storage = std::make_shared<std::vector<chunk_t>>(2, 0x0000);
MemSlice slice(storage);
slice.setUnit(0, 0x12);
slice.setUnit(1, 0x34);
chunk_t chunk = slice.getChunk(0); // chunk == 0x1234
slice.setChunk(2, 0xABCD);
unit_t u = slice.getUnit(2); // u == get_high(0xABCD)
```

## Test Coverage
Comprehensive unit tests for MemSlice are in `tests/test_mem_classes.cpp`, covering:
- Unit and chunk access
- Out-of-range and misaligned access
- Read/write correctness
