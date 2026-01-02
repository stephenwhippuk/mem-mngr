# Memory Manager Experiment: High-Level Overview

## Purpose
This experiment demonstrates a modular, extensible memory management system in C++20. It provides abstractions for memory allocation, paged memory contexts, and fine-grained memory access, suitable for systems programming, emulation, or educational use.

## Architecture
- **MemAlloc**: Manages allocation and deallocation of fixed-size memory blocks, identified by unique IDs.
- **MemSlice**: Provides byte- and word-level access to a memory region (block), with bounds and alignment checking.
- **PagedContext**: Manages a set of memory pages (blocks), allowing dynamic allocation and switching between pages. Provides access to the current page via MemSlice.
- **SequentialPageContext**: Manages paged memory with a sequential access model, maintaining a current page and offset for stream-like access.
- **MemUnit**: High-level manager for multiple memory contexts. Supports creation, lookup, and deletion of contexts.
- **SequentialPageMemAccess**: Provides sequential (stream-like) access to memory managed by SequentialPageContext, supporting unit/chunk access and jumping to arbitrary locations.
- **Primitives**: Utility functions for manipulating 16-bit words and 8-bit bytes.

## Typical Usage
### Paged Access
1. **Create a MemUnit**: The main entry point for managing memory contexts.
2. **Create a Context**: Use `MemUnit::CreatePagedContext(id)` to create a paged memory context.
3. **Switch Pages**: Use `PagedContext::SetPage(pageIndex)` to select or allocate a page.
4. **Access Memory**: Use `PagedContext::getAccessor()` and dynamic cast to `MemSlice*` for fine-grained access.
5. **Read/Write Data**: Use `MemSlice::setUnit`, `getUnit`, `setChunk`, and `getChunk` to manipulate memory.
6. **Delete Contexts**: Use `MemUnit::DeleteContext(id)` to clean up.

### Sequential Access
1. **Create a MemUnit**: The main entry point for managing memory contexts.
2. **Create a Context**: Use `MemUnit::CreateSequentialPageContext(id)` to create a sequential page context.
3. **Set Page**: Use `SequentialPageContext::SetPage(pageIndex)` to select or allocate a page.
4. **Access Memory**: Use `SequentialPageContext::getAccessor()` and dynamic cast to `SequentialPageMemAccess*` for stream-like access.
5. **Read/Write Data**: Use `SequentialPageMemAccess::setUnit`, `getUnit`, `setChunk`, and `getChunk` to manipulate memory at the current offset. Use `jumpTo(page, offset)` to move.
6. **Delete Contexts**: Use `MemUnit::DeleteContext(id)` to clean up.

## Example
### Paged Access
```cpp
#include "memunit.h"
using namespace memmngr;

MemUnit unit;
word_t ctxId = 1;
unit.CreatePagedContext(ctxId);
auto ctx = unit.GetContext(ctxId);
auto pagedCtx = dynamic_cast<PagedContext*>(ctx.get());
pagedCtx->SetPage(0);
IMemAccess& accessor = pagedCtx->getAccessor();
auto memSlice = dynamic_cast<MemSlice*>(&accessor);
memSlice->setUnit(0, 0x42);
unit_t value = memSlice->getUnit(0); // value == 0x42
unit.DeleteContext(ctxId);
```

### Sequential Access
```cpp
#include "memunit.h"
using namespace memmngr;

MemUnit unit;
word_t ctxId = 2;
unit.CreateSequentialPageContext(ctxId);
auto ctx = unit.GetContext(ctxId);
auto seqCtx = dynamic_cast<SequentialPageContext*>(ctx.get());
seqCtx->SetPage(0);
IMemAccess& accessor = seqCtx->getAccessor();
auto seqAccess = dynamic_cast<SequentialPageMemAccess*>(&accessor);
seqAccess->setUnit(0x55);
unit_t value = seqAccess->getUnit(); // value == 0x55
seqAccess->jumpTo(1, 0);
seqAccess->setChunk(0xABCD);
unit.DeleteContext(ctxId);
```

## Extensibility
- New context types (e.g., stack, sequential) can be added by implementing `IContext` and extending `MemUnit`.
- The system is designed for testability, with comprehensive unit and integration tests.

## Test Coverage
- All modules are covered by unit and integration tests in `tests/test_mem_classes.cpp` and `tests/test_memalloc.cpp`.

## Documentation
- See the `docs/` directory for detailed technical documentation on each module.
- [MemUnit](memunit.md)
- [PagedContext](pagedcontext.md)
- [SequentialPageContext](sequentialpagecontext.md)
- [MemSlice](memslice.md)
- [SequentialPageMemAccess](sequentialpagememaccess.md)

## Build & Run
- Uses CMake and GoogleTest for building and testing.
- To build and run tests:
  ```sh
  cmake -S . -B build
  cmake --build build
  ./build/mem_mngr_tests
  ```
