#include "memaccess.h"
#include <stdexcept>
namespace memmngr {
    MemSlice::MemSlice(std::shared_ptr<std::vector<chunk_t>> storage_)
        : storage(storage_) {}

    MemSlice::~MemSlice() = default;
    unit_t MemSlice::getUnit(index_t index) const {
        if( index / 2 >= storage->size()) {
            throw std::out_of_range("Index out of range in getUnit");
        }
        chunk_t chunk = (*storage)[index / 2];
        if (index % 2 == 0) {
            return get_high(chunk);
        } else {
            return get_low(chunk);
        }
    }

    chunk_t MemSlice::getChunk(index_t index) const {
        if( index / 2 >= storage->size()) {
            throw std::out_of_range("Index out of range in getChunk");
        }
        if(index % 2 != 0) {
            throw std::invalid_argument("Chunk index must align to chunk boundary");
        }
        return (*storage)[index / 2];
    }
    
    void MemSlice::setUnit(index_t index, byte_t value) {
        if( index / 2 >= storage->size()) {
            throw std::out_of_range("Index out of range in setUnit");
        }
        chunk_t& chunk = (*storage)[index / 2];
        if (index % 2 == 0) {
            chunk = set_high(chunk, value);
        } else {
            chunk = set_low(chunk, value);
        }
    }
    void MemSlice::setChunk(index_t index, chunk_t value) {
        if( index / 2 >= storage->size()) {
            throw std::out_of_range("Index out of range in setChunk");
        }
        if(index % 2 != 0) {
            throw std::invalid_argument("Chunk index must align to chunk boundary");
        }
        (*storage)[index / 2] = value;
    }
} // namespace memmngr