#include "memalloc.h"
#include <gtest/gtest.h>

using namespace memmngr;

TEST(MemAllocTest, AllocateDeallocate) {
    MemAlloc allocator(16, 10); // block size 16 words, max 10 blocks
    int blockId = allocator.allocate(1, 8); // allocate 8 words
    EXPECT_GE(blockId, 0);
    if (blockId >= 0) {
        auto block = allocator.getBlock(blockId);
        EXPECT_NE(block, nullptr);
        if (block) {
            EXPECT_EQ(block->size(), 8);
        }
        allocator.deallocate(blockId);
        EXPECT_EQ(allocator.getBlock(blockId), nullptr);
    }
}

TEST(MemAllocTest, MaxBlocks) {
    MemAlloc allocator(4, 2); // only 2 blocks allowed
    int id1 = allocator.allocate(1, 4);
    int id2 = allocator.allocate(2, 4);
    EXPECT_GE(id1, 0);
    EXPECT_GE(id2, 0);
    int id3 = allocator.allocate(3, 4);
    EXPECT_EQ(id3, -1); // should fail, max blocks reached
}
