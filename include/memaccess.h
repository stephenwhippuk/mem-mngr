#pragma once
#include "vtypes.h"
#include <memory>
#include <vector>
#include <memory>
#include "primitives.h"
#include "context.h"

namespace memmngr {
    class IMemAccess {
    public:
        virtual ~IMemAccess() = default;
    };

    class MemSlice : public IMemAccess {
        public:
        MemSlice(std::shared_ptr<std::vector<chunk_t>> storage);
        ~MemSlice() override;
        unit_t getUnit(index_t index) const;
        chunk_t getChunk(index_t index) const;
        void setUnit(index_t index, unit_t value);
        void setChunk(index_t index, chunk_t value);

    private:
        std::shared_ptr<std::vector<chunk_t>> storage;
    };

    // forward declare
    class SequentialPageContext;

    class SequentialPageMemAccess : public IMemAccess {
    public:
        SequentialPageMemAccess(SequentialPageContext& context, word_t pageSize);
        ~SequentialPageMemAccess() override;
        unit_t getUnit() const;
        chunk_t getChunk() const;
        void setUnit(unit_t value);
        void setChunk(chunk_t value);
        void jumpTo(word_t pageIndex, word_t offset);
    private:
        SequentialPageContext& m_context;
        word_t m_pageSize;
    };

} // namespace memmngr  