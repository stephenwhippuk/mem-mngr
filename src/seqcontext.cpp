#include "context.h"
#include "memaccess.h"
#include <stdexcept>
namespace memmngr{
    SequentialPageContext::SequentialPageContext(word_t id, MemAlloc& allocator, word_t pageSize, word_t initialCount)
    : m_id(id), m_allocator(allocator), m_pageSize(pageSize), m_currentPage(0), m_currentOffset(0), m_initialCount(initialCount)
    {
        // Constructor implementation
        for(word_t i = 0; i < m_initialCount; ++i) {
            m_allocator.allocate(i, m_pageSize);
        }
    }

    SequentialPageContext::~SequentialPageContext()
    {
        // Destructor implementation
        
    }

    IMemAccess& SequentialPageContext::getAccessor()
    {
        return *(new SequentialPageMemAccess(*this, m_pageSize));
    }

    void SequentialPageContext::incrementOffset(word_t amount)
    {
        m_currentOffset += amount;
        if(m_currentOffset >= m_pageSize) {
            m_currentOffset = 0;
            m_currentPage += 1;
            auto block = m_allocator.getBlock(m_currentPage);
            if(!block) {
                // allocate for now (later will have a flag to error or allocate)
                int res = m_allocator.allocate(m_currentPage, m_pageSize);
            }
        }
    }

    void SequentialPageContext::SetPage(word_t pageIndex)
    {
        auto block = m_allocator.getBlock(pageIndex);
        if(!block) {
            // allocate for now (later will have a flag to error or allocate)
            int res = m_allocator.allocate(pageIndex, m_pageSize);
        }
        m_currentPage = pageIndex;
        m_currentOffset = 0;
    }

    slice_t SequentialPageContext::getCurrentSlice()
    {
        auto block = m_allocator.getBlock(m_currentPage);
        if(!block) {
            throw std::runtime_error("No block allocated for current page");
        }
        return block;
    }
}