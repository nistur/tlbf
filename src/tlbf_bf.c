#include "tlbf_internal.h"

tlbfReturn tlbfBfGetSymbol(tlbfContext* context, tlbfSymbol* symbol)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(symbol, INVALID_INPUT);

    *symbol = TLBF_SYMBOL_UNKNOWN;
    if(context->m_CurrentInstruction == '\0')
    {
	*symbol = TLBF_SYMBOL_EOF;
	tlbfReturnCode(EOF);
    }

    for(tlbfSymbol iSym = TLBF_SYMBOL_INCREMENT_CELL; iSym <= TLBF_SYMBOL_OUTPUT; ++iSym)
    {
	if(*context->m_CurrentInstruction  == tlbfBfCommands[iSym])
	{
	    *symbol = iSym;
	    break;
	}
    }

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfNext(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    context->m_CurrentInstruction++;
    if(*context->m_CurrentInstruction == '\0')
	tlbfReturnCode(EOF);

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfInit(tlbfContext* context, tlbfGetSymbol* getSymbol)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(getSymbol, INVALID_INPUT);

    context->m_InstructionSet[TLBF_SYMBOL_INCREMENT_CELL] = tlbfBfIncrementCell;
    context->m_InstructionSet[TLBF_SYMBOL_DECREMENT_CELL] = tlbfBfDecrementCell;
    context->m_InstructionSet[TLBF_SYMBOL_INCREMENT_PTR]  = tlbfBfIncrementPtr;
    context->m_InstructionSet[TLBF_SYMBOL_DECREMENT_PTR]  = tlbfBfDecrementPtr;
    context->m_InstructionSet[TLBF_SYMBOL_LOOP_START]     = tlbfBfLoopStart;
    context->m_InstructionSet[TLBF_SYMBOL_LOOP_END]       = tlbfBfLoopEnd;
    context->m_InstructionSet[TLBF_SYMBOL_OUTPUT]         = tlbfBfOutput;
    context->m_InstructionSet[TLBF_SYMBOL_INPUT]          = tlbfBfInput;

    *getSymbol = tlbfBfGetSymbol;

    context->m_Next = tlbfBfNext;
    
    tlbfReturnCode(SUCCESS);
}
