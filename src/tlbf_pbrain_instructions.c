#include "tlbf_internal.h"
#include "stdio.h"

const char* sk_procType      = "PBPR";
const char* sk_callstackType = "PBCS";

tlbfReturn tlbfPbrainGetProc(tlbfContext* context, tlbfCell name, tlbfPbrainProc** proc)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(proc, INVALID_INPUT);
    
    tlbfExtData** procs = NULL;
    tlbfReturnCheck(tlbfGetExtData(context, *(int*)sk_procType, &procs));
    tlbfExtData** pProc = procs;
    while(*pProc)
    {
	if(((tlbfPbrainProc*)*pProc)->m_Name == name)
	{
	    *proc = (tlbfPbrainProc*)*pProc;
	    break;
	}
	++pProc;
    }

    tlbfFreeExtDataList(context, &procs);
    
    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfPbrainStartProc(tlbfContext* context)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);

    tlbfCell name = TLBF_CELL;

    tlbfPbrainProc* oldProc = NULL;
    tlbfReturnCheck(tlbfPbrainGetProc(context, name, &oldProc));
    if(oldProc)
    {
	tlbfReturnCheck(tlbfRemoveExtData(context, (tlbfExtData*)oldProc));
	tlbfFree(oldProc);
    }
    
    // store this as a proc
    tlbfPbrainProc* proc = tlbfMalloc(tlbfPbrainProc);

    tlbfReturnCheck(context->m_Next(context));

    proc->m_Start = context->m_CurrentInstruction;
    proc->m_Name = name;
    
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

    tlbfCell name = TLBF_CELL;

    tlbfPbrainProc* proc = NULL;
    tlbfReturnCheck(tlbfPbrainGetProc(context, name, &proc));
    if(proc)
    {
	tlbfPbrainCallstack* callstack = tlbfMalloc(tlbfPbrainCallstack);
	callstack->m_ReturnInstruction = context->m_CurrentInstruction;
	tlbfAddExtData(context, (tlbfExtData*)callstack, *(int*)sk_callstackType);
	
       	context->m_CurrentInstruction = proc->m_Start;
	tlbfReturnCode(SUCCESS);
    }

    tlbfReturnCode(INVALID_INPUT);
}
