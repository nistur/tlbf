#include "tlbf_internal.h"
#include <string.h>

#define TLBF_OOK_INCREMENT_CELL "Ook. Ook."
#define TLBF_OOK_DECREMENT_CELL "Ook! Ook!"
#define TLBF_OOK_INCREMENT_PTR  "Ook. Ook?"
#define TLBF_OOK_DECREMENT_PTR  "Ook? Ook."
#define TLBF_OOK_LOOP_START     "Ook! Ook?"
#define TLBF_OOK_LOOP_END       "Ook? Ook!"
#define TLBF_OOK_INPUT          "Ook. Ook!"
#define TLBF_OOK_OUTPUT         "Ook! Ook."

static const char* tlbfOokCommands[] = 
{
    TLBF_OOK_INCREMENT_CELL,
    TLBF_OOK_DECREMENT_CELL,
    TLBF_OOK_INCREMENT_PTR,
    TLBF_OOK_DECREMENT_PTR,
    TLBF_OOK_LOOP_START,
    TLBF_OOK_LOOP_END,
    TLBF_OOK_INPUT,
    TLBF_OOK_OUTPUT
};

tlbfReturn tlbfOokGetSymbol(tlbfContext* context, tlbfSymbol* symbol)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(symbol, INVALID_INPUT);

    // an Ook command follows the format: 'Ook* Ook*' where * 
    // is one of the following: .?!
    // The pattern of these defines which bf command it maps to
    // it's handy however, as that means that every command is
    // precisely 10 bytes long, if null terminated
    char command[10];
    command[9] = '\0';
    memcpy(command, context->m_CurrentInstruction, 9);

    *symbol = TLBF_SYMBOL_UNKNOWN;

    if(strlen(command) == 0)
    {
	*symbol = TLBF_SYMBOL_EOF;
    }
    else
    {
	for(tlbfSymbol iSym = TLBF_SYMBOL_INCREMENT_PTR; iSym <= TLBF_SYMBOL_OUTPUT; ++iSym)
	{
	    if(strcmp(command, tlbfOokCommands[iSym]) == 0)
	    {
		*symbol = iSym;
		break;
	    }
	}
    }

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfOokNext(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    if(strlen(context->m_CurrentInstruction) <= 10)
	tlbfReturnCode(EOF);

    context->m_CurrentInstruction += 10;

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfOokInit(tlbfContext* context, tlbfGetSymbol* getSymbol)
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

    *getSymbol = tlbfOokGetSymbol;

    context->m_Next = tlbfOokNext;
    
    tlbfReturnCode(SUCCESS);
}
