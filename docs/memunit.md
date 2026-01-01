# MemUnit Module Documentation

## Overview
`MemUnit` is a manager class responsible for creating, storing, and deleting memory contexts. It supports multiple context types (currently PagedContext) and provides lookup and lifecycle management for these contexts. `MemUnit` is the main entry point for higher-level memory management in the experiment.

## Types
- `word_t`: 16-bit unsigned integer (from `vtypes.h`)
- `IContext`: Abstract interface for memory contexts (from `context.h`)
- `PagedContext`: Page-based memory context (from `context.h`)

## Construction
```
MemUnit();
```
- Default constructor initializes an empty context map.

## Methods

### CreatePagedContext
```
void CreatePagedContext(word_t id);
```
- **Description:** Creates a new `PagedContext` with the given ID. Throws `std::invalid_argument` if a context with the same ID already exists.

### CreateStackContext / CreateSequentialPageContext
```
void CreateStackContext(word_t id);
void CreateSequentialPageContext(word_t id);
```
- **Description:** (Not yet implemented) Intended for future context types.

### GetContext
```
std::shared_ptr<IContext> GetContext(word_t id);
```
- **Description:** Returns a shared pointer to the context with the given ID, or `nullptr` if not found.

### DeleteContext
```
void DeleteContext(word_t id);
```
- **Description:** Removes the context with the given ID from the manager.

## Usage Example
```cpp
#include "memunit.h"
MemUnit unit;
unit.CreatePagedContext(42);
auto ctx = unit.GetContext(42);
unit.DeleteContext(42);
```

## Test Coverage
Unit and integration tests for MemUnit are in `tests/test_mem_classes.cpp`, covering:
- Context creation and deletion
- Lookup and lifecycle
- Integration with PagedContext and MemSlice
