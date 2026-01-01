# Memory Manager Experiment: High-Level Overview

## Purpose
This experiment demonstrates a modular, extensible memory management system in C++20. It provides abstractions for memory allocation, paged memory contexts, and fine-grained memory access, suitable for systems programming, emulation, or educational use.

## Architecture
- **MemAlloc**: Manages allocation and deallocation of fixed-size memory blocks, identified by unique IDs.
- **MemSlice**: Provides byte- and word-level access to a memory region (block), with bounds and alignment checking.
- **PagedContext**: Manages a set of memory pages (blocks), allowing dynamic allocation and switching between pages. Provides access to the current page via MemSlice.
- **MemUnit**: High-level manager for multiple memory contexts. Supports creation, lookup, and deletion of contexts.
- **Primitives**: Utility functions for manipulating 16-bit words and 8-bit bytes.

## Typical Usage
1. **Create a MemUnit**: The main entry point for managing memory contexts.
2. **Create a Context**: Use `MemUnit::CreatePagedContext(id)` to create a paged memory context.
3. **Switch Pages**: Use `PagedContext::SetPage(pageIndex)` to select or allocate a page.
4. **Access Memory**: Use `PagedContext::getAccessor()` and dynamic cast to `MemSlice*` for fine-grained access.
5. **Read/Write Data**: Use `MemSlice::setUnit`, `getUnit`, `setChunk`, and `getChunk` to manipulate memory.
6. **Delete Contexts**: Use `MemUnit::DeleteContext(id)` to clean up.

## Example
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

## Extensibility
- New context types (e.g., stack, sequential) can be added by implementing `IContext` and extending `MemUnit`.
- The system is designed for testability, with comprehensive unit and integration tests.

## Test Coverage
- All modules are covered by unit and integration tests in `tests/test_mem_classes.cpp` and `tests/test_memalloc.cpp`.

## Documentation
- See the `docs/` directory for detailed technical documentation on each module.

## Build & Run
- Uses CMake and GoogleTest for building and testing.
- To build and run tests:
  ```sh
  cmake -S . -B build
  cmake --build build
  ./build/mem_mngr_tests
  ```
