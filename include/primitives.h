#pragma once
#include <cstddef>
#include "vtypes.h"
namespace memmngr {


    word_t set_low(word_t original, byte_t low) ;
    word_t set_high(word_t original, byte_t high) ;
    byte_t get_low(word_t value) ;
    byte_t get_high(word_t value) ;

} // namespace primitives