#pragma once
#include "vtypes.h"
#include <memory>
#include <vector>
#include <memory>
#include "primitives.h"

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

} // namespace memmngr  