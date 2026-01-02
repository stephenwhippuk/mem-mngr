
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

    // the sequential page context is similar to a paged context only it maintains a current pointer
    // The accessor it provides is always to the current page and advances the page when the end is reached
    // therefore providing the basic mechanism for code memory execution, it can also be moved 
    // to specific page/offset as needed to provide branching capabilities
    class SequentialPageContext : public IContext {
    public:
        SequentialPageContext(word_t id, MemAlloc& allocator, word_t pageSize, word_t initialCount);
        ~SequentialPageContext() override;
        IMemAccess& getAccessor() override;
        void incrementOffset(word_t amount);
        void SetPage(word_t pageIndex);
    private:
        friend class SequentialPageMemAccess;
        slice_t getCurrentSlice();
        word_t m_id;
        MemAlloc& m_allocator;
        word_t m_pageSize;
        word_t m_initialCount;
        word_t m_currentPage;
        word_t m_currentOffset; 
    };

} // namespace memmngr