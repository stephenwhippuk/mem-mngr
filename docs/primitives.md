# Primitives Module Documentation

## Overview
The `primitives` module provides low-level bitwise operations for manipulating 16-bit words (`word_t`) and 8-bit bytes (`byte_t`). These utilities are essential for memory management and data packing/unpacking in the memory manager experiment.

## Types
- `word_t`: 16-bit unsigned integer (from `vtypes.h`)
- `byte_t`: 8-bit unsigned integer (from `vtypes.h`)

## Functions

### set_low
```
word_t set_low(word_t original, byte_t low);
```
- **Description:** Sets the low (least significant) byte of a 16-bit word to `low`, preserving the high byte.
- **Example:**
  - `set_low(0xABCD, 0x12)` returns `0xAB12`

### set_high
```
word_t set_high(word_t original, byte_t high);
```
- **Description:** Sets the high (most significant) byte of a 16-bit word to `high`, preserving the low byte.
- **Example:**
  - `set_high(0xABCD, 0x34)` returns `0x34CD`

### get_low
```
byte_t get_low(word_t value);
```
- **Description:** Extracts the low (least significant) byte from a 16-bit word.
- **Example:**
  - `get_low(0x1234)` returns `0x34`

### get_high
```
byte_t get_high(word_t value);
```
- **Description:** Extracts the high (most significant) byte from a 16-bit word.
- **Example:**
  - `get_high(0x1234)` returns `0x12`

## Usage Example
```cpp
word_t w = 0x0000;
w = set_high(w, 0x56); // w = 0x5600
w = set_low(w, 0x78);  // w = 0x5678
byte_t hi = get_high(w); // hi = 0x56
byte_t lo = get_low(w);  // lo = 0x78
```

## Test Coverage
All functions are covered by unit tests in `tests/test_mem_classes.cpp`.
