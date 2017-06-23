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
int numOpenLoops = 0;
#define TLBF_COUNT_LOOP(cnt, list)		       \
    int cnt = 0;				       \
    {						       \
	tlbfLoopNode* _ = list;			       \
	while(_)				       \
	{					       \
	    cnt++;				       \
	    _ = _->m_Next;			       \
	}					       \
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
	numOpenLoops++;
	TLBF_COUNT_LOOP(numUsed, context->m_LastLoopNode);
	TLBF_COUNT_LOOP(numFree, context->m_FreeLoopNode);
//	printf("Loop Start: %d (%d/%d)\n", numOpenLoops, numUsed, numFree);
    }
    else
    {
	int loopCount = 1;
	while(1)
	{
	    tlbfReturnCheck(context->m_Next(context));
	    if(*context->m_CurrentInstruction == '[')
		loopCount++;
	    else if(*context->m_CurrentInstruction == ']')
		if((--loopCount) <= 0)
		    break;
	}
//	printf("Loop Start-End\n");
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
	numOpenLoops--;
	TLBF_COUNT_LOOP(numUsed, context->m_LastLoopNode);
	TLBF_COUNT_LOOP(numFree, context->m_FreeLoopNode);
//	printf("Loop Start: %d (%d/%d)\n", numOpenLoops, numUsed, numFree);
    }
    else
    {
	context->m_CurrentInstruction = context->m_LastLoopNode->m_LoopStart;
//	printf("Loop\n");
    }

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfBfOutput       (tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    printf("%c", TLBF_CELL);
//  fflush(stdout); // This should really be in here so that it flushes output properly
                    // however, the testsuite breaks if it is here, as flushing will
                    // reset to the beginning of the buffer the testsuite uses to
                    // capture the output. I need to establish how I can fix this.

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
