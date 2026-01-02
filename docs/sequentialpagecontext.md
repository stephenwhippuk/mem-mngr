# SequentialPageContext Documentation

## Overview
`SequentialPageContext` manages paged memory with a sequential access model. It maintains a current page and offset, allowing stream-like access to memory. It is designed for scenarios where memory is accessed in a linear or program-counter-like fashion, such as code execution or sequential data processing.

## Types
- `word_t`: 16-bit unsigned integer (from `vtypes.h`)
- `MemAlloc`: Memory allocator (from `memalloc.h`)
- `SequentialPageMemAccess`: Accessor for sequential memory (from `memaccess.h`)
- `IMemAccess`: Interface for memory access

## Construction
```
SequentialPageContext(word_t id, MemAlloc& allocator, word_t pageSize, word_t initialCount);
```
- **id**: Unique identifier for the context
- **allocator**: Reference to a `MemAlloc` instance
- **pageSize**: Size of each page in words
- **initialCount**: Number of pages to pre-allocate

## Methods

### getAccessor
```
IMemAccess& getAccessor();
```
- **Description:** Returns a reference to a `SequentialPageMemAccess` for the current page and offset.

### incrementOffset
```
void incrementOffset(word_t amount);
```
- **Description:** Advances the current offset by `amount`. If the offset exceeds the page size, moves to the next page and resets the offset.

### SetPage
```
void SetPage(word_t pageIndex);
```
- **Description:** Switches the current page to `pageIndex` and resets the offset. Allocates the page if it does not exist.

### getCurrentSlice
```
slice_t getCurrentSlice();
```
- **Description:** Returns a shared pointer to the current page's memory block.

## Error Handling
- Throws `std::runtime_error` if accessing a non-allocated page.
- `incrementOffset` allocates a new page if needed.

## Usage Example
```cpp
#include "context.h"
MemAlloc allocator(8, 4);
SequentialPageContext ctx(1, allocator, 8, 2);
ctx.SetPage(0);
IMemAccess& accessor = ctx.getAccessor();
auto seqAccess = dynamic_cast<SequentialPageMemAccess*>(&accessor);
seqAccess->setUnit(0x42);
ctx.incrementOffset(4);
ctx.SetPage(1);
```

## Test Coverage
- Comprehensive unit and integration tests in `tests/test_mem_classes.cpp`.
- Covers sequential access, offset/page management, and error handling.
