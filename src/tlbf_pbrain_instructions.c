#include "tlbf_internal.h"
#include "stdio.h"

const char* sk_procType      = "PBPR";
const char* sk_callstackType = "PBCS";

tlbfReturn tlbfPbrainStartProc(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    // store this as a proc
    tlbfPbrainProc* proc = tlbfMalloc(tlbfPbrainProc);

    tlbfReturnCheck(context->m_Next(context));

    proc->m_Start = context->m_CurrentInstruction;
    
    tlbfAddExtData(context, (tlbfExtData*)proc, *(int*)sk_procType);

    int loopCount = 1;
    while(1)
    {
	tlbfReturnCheck(context->m_Next(context));
	if(*context->m_CurrentInstruction == TLBF_PBRAIN_START_PROC)
	    loopCount++;
	else if(*context->m_CurrentInstruction == TLBF_PBRAIN_END_PROC)
	    if((--loopCount) <= 0)
		break;
    }
    tlbfReturn();
}

tlbfReturn tlbfPbrainEndProc(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    tlbfExtData** callstack = NULL;
    tlbfReturnCheck(tlbfGetExtData(context, *(int*)sk_callstackType, &callstack));
    tlbfExtData* prev = NULL;
    tlbfExtData** curr = callstack;
    while(*curr)
    {
	prev = *curr;
	++curr;
    }

    if(prev)
    {
	context->m_CurrentInstruction = ((tlbfPbrainCallstack*)prev)->m_ReturnInstruction;
	tlbfReturnCheck(tlbfRemoveExtData(context, prev));
	tlbfFree(((tlbfPbrainCallstack*)prev));
	tlbfFreeExtDataList(context, &callstack);
	tlbfReturnCode(SUCCESS);
    }

    tlbfFreeExtDataList(context, &callstack);
    tlbfReturnCode(INVALID_INPUT);
}

tlbfReturn tlbfPbrainCallProc(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    tlbfCell procNum = TLBF_CELL;
    tlbfExtData** procs = NULL;
    tlbfReturnCheck(tlbfGetExtData(context, *(int*)sk_procType, &procs));
    tlbfExtData** proc = procs;
    while(*proc && procNum)
    {
	--procNum;
	++proc;
    }

    if(*proc)
    {
	tlbfPbrainCallstack* callstack = tlbfMalloc(tlbfPbrainCallstack);
	callstack->m_ReturnInstruction = context->m_CurrentInstruction;
	tlbfAddExtData(context, (tlbfExtData*)callstack, *(int*)sk_callstackType);
	tlbfFreeExtDataList(context, &procs);
	
       	context->m_CurrentInstruction = ((tlbfPbrainProc*)*proc)->m_Start;
	tlbfReturnCode(SUCCESS);
    }

    tlbfFreeExtDataList(context, &procs);
    tlbfReturnCode(INVALID_INPUT);
}
