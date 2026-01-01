#include "context.h"
#include "memaccess.h"
#include <stdexcept>
namespace memmngr   
{
    PagedContext::PagedContext(word_t id, MemAlloc& allocator, word_t pageSize, word_t initialCount)
    : m_id(id), m_allocator(allocator), m_pageSize(pageSize), m_currentPage(0), m_initialCount(initialCount)
    {
        // Constructor implementation
        for(word_t i = 0; i < m_initialCount; ++i) {
            m_allocator.allocate(i, m_pageSize);
        }
    }

    PagedContext::~PagedContext()
    {
        // Destructor implementation
        
    }

    IMemAccess& PagedContext::getAccessor()
    {
        auto block = m_allocator.getBlock(m_currentPage);
        if(!block) {
            throw std::runtime_error("No block allocated for current page");
        }
        auto memSlice = new MemSlice(block);
        return *memSlice;
    }

    void PagedContext::SetPage(word_t pageIndex)
    {
        // Method implementation
        auto block = m_allocator.getBlock(pageIndex);
        if(!block) {
            // allocate for now (later will have a flag to error or allocate)
            int res = m_allocator.allocate(pageIndex, m_pageSize);
        }
        m_currentPage = pageIndex;
    }

} // namespace memmngr