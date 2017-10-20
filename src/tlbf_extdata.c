#include "tlbf_internal.h"
#include "util/stb.h"

tlbfReturn tlbfAddExtData(tlbfContext* context, tlbfExtData* data, tlbfExtType type)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(data, INVALID_INPUT);

    data->m_Type = type;
    data->m_Next = NULL;
    
    if(context->m_ExtData == NULL)
    {
	context->m_ExtData = data;
    }
    else
    {
	tlbfExtData* extData = context->m_ExtData;
	while(extData->m_Next)
	{
	    extData = extData->m_Next;
	}
	extData->m_Next = data;
    }

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfRemoveExtData(tlbfContext* context, tlbfExtData* data)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(data, INVALID_INPUT);

    tlbfExtData** extData = &context->m_ExtData;
    while(*extData)
    {
	if(*extData == data)
	{
	    *extData = data->m_Next;
	    break;
	}
	extData = &(*extData)->m_Next;
    }

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfGetExtData(tlbfContext* context, tlbfExtType type, tlbfExtData*** list)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(list, INVALID_INPUT);

    if(*list != NULL)
    {
	tlbfReturnCode(INVALID_INPUT);
    }

    tlbfExtData* extData = context->m_ExtData;
    while(extData)
    {
	if(extData->m_Type == type)
	{
	    sbpush(*list, extData);
	}
	extData = extData->m_Next;
    }
    
    sbpush(*list, NULL);

    tlbfReturnCode(SUCCESS);
}

tlbfReturn tlbfFreeExtDataList(tlbfContext* context, tlbfExtData*** list)
{
    TLBF_NULL_CHECK(context, NO_CONTEXT);
    TLBF_NULL_CHECK(list, INVALID_INPUT);

    sbfree(*list);
    
    tlbfReturnCode(SUCCESS);
}
