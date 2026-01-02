#include "memunit.h"
#include "context.h"
#include <stdexcept>

namespace memmngr {

    void MemUnit::CreatePagedContext(word_t id) {
        if (m_contexts.find(id) != m_contexts.end()) {
            throw std::invalid_argument("Context with given ID already exists");
        }
        // For simplicity, using fixed page size and initial count
        word_t pageSize = 0xFFFF; // example page size
        word_t initialCount = 4; // example initial count
        auto allocator = std::make_shared<MemAlloc>(pageSize, 100); // example max blocks
        auto context = std::make_shared<PagedContext>(id, *allocator, pageSize, initialCount);
        m_contexts[id] = context;
    }

    void MemUnit::CreateStackContext(word_t id) {
        // Implementation for stack context creation
    }

    void MemUnit::CreateSequentialPageContext(word_t id) {
        // Implementation for sequential page context creation
        word_t pageSize = 0xFFFF; // example page size
        word_t initialCount = 4; // example initial count
        auto allocator = std::make_shared<MemAlloc>(pageSize, 100); // example max blocks
        auto context = std::make_shared<SequentialPageContext>(id, *allocator, pageSize, initialCount);
        m_contexts[id] = context;
    }

    std::shared_ptr<IContext> MemUnit::GetContext(word_t id) {
        auto it = m_contexts.find(id);
        if (it != m_contexts.end()) {
            return it->second;
        }
        return nullptr;
    }

    void MemUnit::DeleteContext(word_t id) {
        m_contexts.erase(id);
    }

} // namespace memmngr