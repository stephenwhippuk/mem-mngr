
#include "primitives.h"

namespace memmngr {

// clear low byte and set it to 'low'
word_t set_low(word_t original, byte_t low) {
    return (original & 0xFF00) | low;
}

// clear high byte and set it to 'high'
word_t set_high(word_t original, byte_t high) {
    return (original & 0x00FF) | (static_cast<word_t>(high) << 8);
}

byte_t get_low(word_t value) {
    return static_cast<byte_t>(value & 0x00FF);
}

byte_t get_high(word_t value) {
    return static_cast<byte_t>((value >> 8) & 0x00FF);
}

} // namespace memmngr