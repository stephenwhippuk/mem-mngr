# PagedContext Module Documentation

## Overview
`PagedContext` is a class that manages paged memory using a `MemAlloc` allocator. It provides page-based access to memory, allowing dynamic allocation and switching between pages. Each page is a block of memory of fixed size, and access is provided via `MemSlice` objects.

## Types
- `word_t`: 16-bit unsigned integer (from `vtypes.h`)
- `MemAlloc`: Memory allocator class (from `memalloc.h`)
- `MemSlice`: Memory access class (from `memaccess.h`)
- `IMemAccess`: Interface for memory access

## Construction
```
PagedContext(word_t id, MemAlloc& allocator, word_t pageSize, word_t initialCount);
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
- **Description:** Returns a reference to a `MemSlice` for the current page. Throws `std::runtime_error` if the current page is not allocated.

### SetPage
```
void SetPage(word_t pageIndex);
```
- **Description:** Switches the current page to `pageIndex`. If the page is not allocated, it will be allocated on demand.

## Error Handling
- `getAccessor` throws `std::runtime_error` if the current page is not allocated.
- `SetPage` allocates the page if it does not exist (current implementation).

## Usage Example
```cpp
#include "context.h"
MemAlloc allocator(8, 4);
PagedContext ctx(1, allocator, 8, 2);
ctx.SetPage(0);
IMemAccess& accessor = ctx.getAccessor();
// Use dynamic_cast<MemSlice*>(&accessor) to access MemSlice methods
```

## Test Coverage
Unit and integration tests for PagedContext are in `tests/test_mem_classes.cpp`, covering:
- Page allocation and switching
- Accessor retrieval
- Integration with MemUnit and MemSlice
