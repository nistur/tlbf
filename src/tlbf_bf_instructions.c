#include "tlbf_internal.h"
#include <stdio.h>

//#define TLBF_BOUNDS_CHECK
#define TLBF_LOOP_CELLS

tlbfReturn tlbfBfIncrementCell(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    TLBF_CELL++;

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfDecrementCell(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    TLBF_CELL--;

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfIncrementPtr (tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    context->m_CurrentCell++;
#ifdef TLBF_LOOP_CELLS
    if(context->m_CurrentCell >= TLBF_CELL_COUNT)
    {
	context->m_CurrentCell = 0;
    }
#elif TLBF_BOUNDS_CHECK
    if(context->m_CurrentCell >= TLBF_CELL_COUNT)
    {
	tlbfReturnCode(OUT_OF_RANGE);
    }
#endif


    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfDecrementPtr (tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    context->m_CurrentCell--;
#ifdef TLBF_LOOP_CELLS
    if(context->m_CurrentCell < 0)
    {
	context->m_CurrentCell = TLBF_CELL_COUNT-1;
    }
#elif TLBF_BOUNDS_CHECK
    if(context->m_CurrentCell < 0)
    {
	tlbfReturnCode(OUT_OF_RANGE);
    }
#endif
    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfLoopStart    (tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    if(TLBF_CELL != 0)
    {
	tlbfLoopNode* node = context->m_FreeLoopNode;
	context->m_FreeLoopNode = node->m_Next;
	node->m_Next = context->m_LastLoopNode;
	context->m_LastLoopNode = node;
	context->m_LastLoopNode->m_LoopStart = context->m_CurrentInstruction;
    }
    else
    {
	int loopCount = 0;
	while(1)
	{
	    tlbfReturnCheck(context->m_Next(context));
	    if(*context->m_CurrentInstruction == '[')
		loopCount++;
	    else if(*context->m_CurrentInstruction == ']')
		if(--loopCount)
		    break;
	}
    }

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfLoopEnd      (tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    if(TLBF_CELL == 0)
    {
	tlbfLoopNode* prevFree = context->m_FreeLoopNode;
	context->m_FreeLoopNode = context->m_LastLoopNode;
	context->m_LastLoopNode = context->m_FreeLoopNode->m_Next;
	context->m_FreeLoopNode->m_Next = prevFree;
    }
    else
    {
	context->m_CurrentInstruction = context->m_LastLoopNode->m_LoopStart;
    }

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfOutput       (tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    printf("%c", TLBF_CELL);
    fflush(stdout);

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfInput        (tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    int c = getchar();
    if(c & ~0xFF)
    {
	tlbfReturnCode(OUT_OF_RANGE);
    }
    TLBF_CELL = (tlbfCell)c;

    tlbfReturnCode(SUCCESS);
}
