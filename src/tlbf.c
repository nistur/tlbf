#include "tlbf_internal.h"
#include <string.h>

tlbfReturn tlbfClearContext(tlbfContext* context)
{
    int i;
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    memset(context->m_Cells, 0, TLBF_CELL_COUNT);
    context->m_CurrentCell = 0 + TLBF_NEG_CELLS;
    context->m_LastLoopNode = 0;
    context->m_FreeLoopNode = &context->m_LoopNodes[0];

    for(i = 0; i < TLBF_LOOP_COUNT-1; ++i)
	context->m_LoopNodes[i].m_Next = &context->m_LoopNodes[i+1];
    context->m_LoopNodes[TLBF_LOOP_COUNT-1].m_Next = 0;
    
    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfInitContext(tlbfContext** context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    *context = tlbfMalloc(tlbfContext);
    if(tlbfClearContext(*context) != TLBF_SUCCESS)
	   tlbfTerminateContext(context);

    (*context)->m_Flags |= TLBF_LANG_BF;

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfTerminateContext(tlbfContext** context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    tlbfFree(*context);
    *context = 0;
    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfSetProgram(tlbfContext* context, tlbfProgram program)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    context->m_Program = program;
    context->m_CurrentInstruction = &context->m_Program[0];

    tlbfReturnCode(SUCCESS);
}
#include <stdio.h>
tlbfReturn tlbfRun(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    tlbfGetSymbol getSymbol = 0;
    tlbfReturn stat = TLBF_SUCCESS;

    if(context->m_Flags & TLBF_LANG_BF)
    {
	stat = tlbfBfInit(context, &getSymbol);
    }
    else if(context->m_Flags & TLBF_LANG_OOK)
    {
	stat = tlbfOokInit(context, &getSymbol);
    }

    if(stat == TLBF_SUCCESS && context->m_Flags & TLBF_EXT_PBRAIN)
    {
	stat = tlbfPbrainInit(context, &getSymbol);
    }

    while(stat == TLBF_SUCCESS)
    {
	tlbfSymbol sym = TLBF_SYMBOL_UNKNOWN;
	int ind = context->m_CurrentInstruction - context->m_Program;
	stat = getSymbol(context, &sym);
	if(sym != TLBF_SYMBOL_UNKNOWN)
	{
	    stat = stat == TLBF_SUCCESS ? sym == TLBF_SYMBOL_EOF ? TLBF_EOF : TLBF_SUCCESS : stat;
	    stat = stat == TLBF_SUCCESS ? context->m_InstructionSet[sym](context) : stat;
	}
	stat = stat == TLBF_SUCCESS ? context->m_Next(context) : stat;

    }
    if(stat == TLBF_EOF)
	tlbfReturnCode(SUCCESS);

    tlbfReturn();
}

tlbfReturn tlbfNext(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    if(context->m_Flags & TLBF_LANG_BF)
    {
	return tlbfBfNext(context);
    }
    else if(context->m_Flags & TLBF_LANG_OOK)
    {
	return tlbfOokNext(context);
    }
    
    tlbfReturnCode(INVALID_INPUT);
}

const char* tlbfError()
{
    return g_tlbfErrors[g_tlbfError];
}
