#include "memalloc.h"
#include <stdexcept>

namespace memmngr {

    MemAlloc::MemAlloc(dword_t blockSize, dword_t maxBlocks)
        : m_blockSize(blockSize), m_blockCount(maxBlocks) {
        if (static_cast<dword_t>(blockSize) * static_cast<dword_t>(maxBlocks) > 4294967296) {
            throw std::invalid_argument("Total memory allocation exceeds 4.3GB limit");
        }
    }

    MemAlloc::~MemAlloc() {
        m_blocks.clear();
    }

    int MemAlloc::allocate(word_t id, word_t words) {
        if (words > m_blockSize) {
            return -1;
        }
        if (m_blocks.size() >= m_blockCount) {
            return -1;
        }
        if (m_blocks.find(id) != m_blocks.end()) {
            return -1;
        }
        auto block = std::make_shared<block_t>(words, 0);
        m_blocks[id] = block;
        return id;
    }

    void MemAlloc::deallocate(word_t blockId) {
        m_blocks.erase(blockId);
    }

    std::shared_ptr<block_t> MemAlloc::getBlock(word_t blockId) {
        auto it = m_blocks.find(blockId);
        if (it != m_blocks.end()) {
            return it->second;
        }
        return nullptr;
    }

} // namespace memmngr