#include "memaccess.h"
#include <stdexcept>
namespace memmngr {
    SequentialPageMemAccess::SequentialPageMemAccess(SequentialPageContext& context, word_t pageSize)
        : m_context(context), m_pageSize(pageSize) {}

    SequentialPageMemAccess::~SequentialPageMemAccess() = default;

    unit_t SequentialPageMemAccess::getUnit() const {
        auto slice = m_context.getCurrentSlice();
        word_t offset = m_context.m_currentOffset;
        if( offset / 2 >= slice->size()) {
            throw std::out_of_range("Offset out of range in getUnit");
        }
        chunk_t chunk = (*slice)[offset / 2];
        if (offset % 2 == 0) {
            return get_high(chunk);
        } else {
            return get_low(chunk);
        }
    }

    chunk_t SequentialPageMemAccess::getChunk() const {
        auto slice = m_context.getCurrentSlice();
        word_t offset = m_context.m_currentOffset;
        if( offset / 2 >= slice->size()) {
            throw std::out_of_range("Offset out of range in getChunk");
        }
        if(offset % 2 != 0) {
            throw std::invalid_argument("Chunk offset must align to chunk boundary");
        }
        return (*slice)[offset / 2];
    }
    void SequentialPageMemAccess::setUnit(unit_t value) {
        auto slice = m_context.getCurrentSlice();
        word_t offset = m_context.m_currentOffset;
        if( offset / 2 >= slice->size()) {
            throw std::out_of_range("Offset out of range in setUnit");
        }
        chunk_t& chunk = (*slice)[offset / 2];
        if (offset % 2 == 0) {
            chunk = set_high(chunk, value);
        } else {
            chunk = set_low(chunk, value);
        }
    }
    void SequentialPageMemAccess::setChunk(chunk_t value) {
        auto slice = m_context.getCurrentSlice();
        word_t offset = m_context.m_currentOffset;
        if( offset / 2 >= slice->size()) {
            throw std::out_of_range("Offset out of range in setChunk");
        }
        if(offset % 2 != 0) {
            throw std::invalid_argument("Chunk offset must align to chunk boundary");
        }
        (*slice)[offset / 2] = value;
    }
    void SequentialPageMemAccess::jumpTo(word_t pageIndex, word_t offset) {
        m_context.SetPage(pageIndex);
        m_context.m_currentOffset = offset;
    }
} // namespace memmngr