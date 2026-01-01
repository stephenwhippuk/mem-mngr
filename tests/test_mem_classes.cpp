#include "memunit.h"
#include "memaccess.h"
#include "context.h"
#include "primitives.h"
#include <gtest/gtest.h>
#include <memory>

using namespace memmngr;

TEST(MemSliceTest, BasicUnitAccess) {
    auto storage = std::make_shared<std::vector<chunk_t>>(2, 0x1234);
    MemSlice slice(storage);
    EXPECT_NO_THROW(slice.setUnit(0, 0x12));
    EXPECT_NO_THROW(slice.setUnit(1, 0x34));
    EXPECT_EQ(slice.getUnit(0), get_high(0x1234));
    EXPECT_EQ(slice.getUnit(1), get_low(0x1234));
}

TEST(PagedContextTest, PageAllocationAndAccess) {
    MemAlloc allocator(8, 4);
    PagedContext ctx(1, allocator, 8, 2);
    EXPECT_NO_THROW(ctx.SetPage(0));
    EXPECT_NO_THROW(ctx.SetPage(1));
    EXPECT_NO_THROW(ctx.SetPage(5)); // Out of range, but allocates
}

TEST(MemUnitTest, ContextLifecycle) {
    MemUnit unit;
    EXPECT_NO_THROW(unit.CreatePagedContext(42));
    auto ctx = unit.GetContext(42);
    EXPECT_NE(ctx, nullptr);
    unit.DeleteContext(42);
    EXPECT_EQ(unit.GetContext(42), nullptr);
}

TEST(IntegrationTest, MemUnitPageContextAccess) {
    MemUnit unit;
    word_t ctxId = 100;
    unit.CreatePagedContext(ctxId);
    auto ctx = unit.GetContext(ctxId);
    ASSERT_NE(ctx, nullptr);
    // Dynamic cast to PagedContext
    auto pagedCtx = dynamic_cast<PagedContext*>(ctx.get());
    ASSERT_NE(pagedCtx, nullptr);
    pagedCtx->SetPage(0);
    IMemAccess& accessor = pagedCtx->getAccessor();
    // Dynamic cast to MemSlice
    auto memSlice = dynamic_cast<MemSlice*>(&accessor);
    ASSERT_NE(memSlice, nullptr);
    // Test access to memory
    EXPECT_NO_THROW(memSlice->setUnit(0, 0xAB));
    EXPECT_EQ(memSlice->getUnit(0), 0xAB);
}

// Primitives tests

using namespace memmngr;

TEST(PrimitivesTest, SetLow) {
    word_t original = 0xABCD;
    byte_t low = 0x12;
    word_t result = set_low(original, low);
    EXPECT_EQ(result, 0xAB12);
}

TEST(PrimitivesTest, SetHigh) {
    word_t original = 0xABCD;
    byte_t high = 0x34;
    word_t result = set_high(original, high);
    EXPECT_EQ(result, 0x34CD);
}

TEST(PrimitivesTest, GetLow) {
    word_t value = 0x1234;
    byte_t low = get_low(value);
    EXPECT_EQ(low, 0x34);
}

TEST(PrimitivesTest, GetHigh) {
    word_t value = 0x1234;
    byte_t high = get_high(value);
    EXPECT_EQ(high, 0x12);
}

TEST(PrimitivesTest, SetAndGetLowHigh) {
    word_t value = 0x0000;
    value = set_high(value, 0x56);
    value = set_low(value, 0x78);
    EXPECT_EQ(get_high(value), 0x56);
    EXPECT_EQ(get_low(value), 0x78);
    EXPECT_EQ(value, 0x5678);
}

// MemSlice comprehensive tests
TEST(MemSliceTest, SetAndGetUnit) {
    auto storage = std::make_shared<std::vector<chunk_t>>(2, 0x0000);
    MemSlice slice(storage);
    slice.setUnit(0, 0x12);
    slice.setUnit(1, 0x34);
    EXPECT_EQ(slice.getUnit(0), 0x12);
    EXPECT_EQ(slice.getUnit(1), 0x34);
}

TEST(MemSliceTest, SetAndGetChunk) {
    auto storage = std::make_shared<std::vector<chunk_t>>(2, 0x0000);
    MemSlice slice(storage);
    slice.setChunk(0, 0xABCD);
    EXPECT_EQ(slice.getChunk(0), 0xABCD);
    slice.setChunk(2, 0x1234);
    EXPECT_EQ(slice.getChunk(2), 0x1234);
}

TEST(MemSliceTest, OutOfRangeUnit) {
    auto storage = std::make_shared<std::vector<chunk_t>>(1, 0x0000);
    MemSlice slice(storage);
    EXPECT_THROW(slice.getUnit(3), std::out_of_range);
    EXPECT_THROW(slice.setUnit(3, 0x56), std::out_of_range);
}

TEST(MemSliceTest, OutOfRangeChunk) {
    auto storage = std::make_shared<std::vector<chunk_t>>(1, 0x0000);
    MemSlice slice(storage);
    EXPECT_THROW(slice.getChunk(2), std::out_of_range);
    EXPECT_THROW(slice.setChunk(2, 0x789A), std::out_of_range);
}

TEST(MemSliceTest, MisalignedChunkAccess) {
    auto storage = std::make_shared<std::vector<chunk_t>>(2, 0x0000);
    MemSlice slice(storage);
    EXPECT_THROW(slice.getChunk(1), std::invalid_argument);
    EXPECT_THROW(slice.setChunk(1, 0xBEEF), std::invalid_argument);
}
