#pragma once
#include <cstddef>
#include <cstdint>
namespace memmngr {
    constexpr const char* VERSION = "0.1.0";

    typedef uint8_t  byte_t;
    typedef uint16_t word_t;
    typedef uint32_t dword_t;

    typedef byte_t unit_t;
    typedef word_t chunk_t;
    typedef word_t index_t;

} // namespace memmngr
