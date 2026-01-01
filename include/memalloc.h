#pragma once
#include "vtypes.h"
#include <map>
#include <vector>
#include <memory>

/* the allocator is responsible for managing memory blocks for a context 
    allocations are in words (16-bits) in order to ensiure that alignment is correct
    each block is identified by a block id (word_t) 
    allocations can be up to dword in size (32-bits) and rhere can be up to dword_t blocks allocated
    however there is a maximum of 4.3GB in total memory that can be allocated by a single MemAlloc instance
    meaning that maxBlocks * blockSize must be <= 4,294,967,296 bytes (2,147,483,648 words)
*/

namespace memmngr {
    typedef std::vector<word_t> block_t;

    class MemAlloc {
    public:
        MemAlloc(dword_t blockSize, dword_t maxBlocks);
        ~MemAlloc();
        int allocate(word_t id, word_t words);
        void deallocate(word_t blockId);
        std::shared_ptr<block_t> getBlock(word_t blockId);
    private:
        dword_t m_blockSize;
        dword_t m_blockCount;
        std::map<word_t, std::shared_ptr<block_t>> m_blocks;
    };
} // namespace memmngr