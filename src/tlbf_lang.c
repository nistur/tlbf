#include "tlbf_internal.h"

tlbfReturn tlbfSetLangFlags(tlbfContext* context, tlbfLangFlags flags)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    
    /* TODO: Check compiled support for flags */

    context->m_Flags = flags;
    
    tlbfReturnCode(SUCCESS);
}
