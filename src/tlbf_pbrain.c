#include "tlbf_internal.h"

tlbfReturn tlbfPbrainGetSymbol(tlbfContext* context, tlbfSymbol* symbol)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(symbol, INVALID_INPUT);

    *symbol = TLBF_SYMBOL_UNKNOWN;
    if(context->m_CurrentInstruction == '\0')
    {
	*symbol = TLBF_SYMBOL_EOF;
	tlbfReturnCode(EOF);
    }

    if(tlbfBfGetSymbol(context, symbol) == TLBF_SUCCESS &&
       *symbol == TLBF_SYMBOL_UNKNOWN)
    {
	for(tlbfSymbol iSym = TLBF_SYMBOL_START_PROC;
	    iSym <= TLBF_SYMBOL_CALL_PROC;
	    ++iSym)
	{
	    if(*context->m_CurrentInstruction == tlbfPbrainCommands[iSym - TLBF_SYMBOL_START_PROC])
	    {
		*symbol = iSym;
		break;
	    }
	}
	tlbfReturnCode(SUCCESS);
    }
    tlbfReturn();
}

tlbfReturn tlbfPbrainInit(tlbfContext* context, tlbfGetSymbol* getSymbol)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(getSymbol, INVALID_INPUT);

    if(!(context->m_Flags & TLBF_LANG_BF))
    {
	tlbfReturnCode(LANGUAGE_MISMATCH);
    }
    
    context->m_InstructionSet[TLBF_SYMBOL_START_PROC] = tlbfPbrainStartProc;
    context->m_InstructionSet[TLBF_SYMBOL_END_PROC]   = tlbfPbrainEndProc;
    context->m_InstructionSet[TLBF_SYMBOL_CALL_PROC]  = tlbfPbrainCallProc;

    *getSymbol = tlbfPbrainGetSymbol;

    tlbfReturnCode(SUCCESS);
}
