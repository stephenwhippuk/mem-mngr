
#pragma once
#include "vtypes.h"
#include <memory>
namespace memmngr {
    class IMemAccess;
}
#include "memalloc.h"
#include <vector>
#include <memory>

namespace memmngr {
    typedef std::shared_ptr<std::vector<word_t>> slice_t;

    class IContext {
    public:
        virtual ~IContext() = default;
        virtual IMemAccess& getAccessor() = 0;
    };  

    // uses page memory and provides MemSlice accessors
    // each allocation is of pageSize
    class PagedContext : public IContext{
    public:
        PagedContext(word_t id, MemAlloc& allocator, word_t pageSize, word_t initialCount);

        ~PagedContext() override;
        IMemAccess& getAccessor() override;
        void SetPage(word_t pageIndex);
    private:
        word_t m_id;
        MemAlloc& m_allocator;
        word_t m_pageSize;
        word_t m_initialCount;
        word_t m_currentPage;
    };

} // namespace memmngr