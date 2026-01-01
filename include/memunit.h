#pragma once
#include "vtypes.h"
#include "memalloc.h"
#include "context.h"

namespace memmngr {

    class MemUnit {
    public:
        void CreatePagedContext(word_t id);
        void CreateStackContext(word_t id);
        void CreateSequentialPageContext(word_t id);
        std::shared_ptr<IContext> GetContext(word_t id);
        void DeleteContext(word_t id);
    private:
        std::map<word_t, std::shared_ptr<IContext>> m_contexts;
    };

} // namespace memmngr