#ifndef __TLBF_PBRAIN_H__
#define __TLBF_PBRAIN_H__

#define TLBF_PBRAIN_START_PROC '{'
#define TLBF_PBRAIN_END_PROC   '}'
#define TLBF_PBRAIN_CALL_PROC  '*'

static const char tlbfPbrainCommands[] =
{
    TLBF_PBRAIN_START_PROC,
    TLBF_PBRAIN_END_PROC,
    TLBF_PBRAIN_CALL_PROC
};

TLBF_INTERNAL_EXPORT tlbfReturn tlbfPbrainInit(tlbfContext* context, tlbfGetSymbol* getSymbol);

TLBF_INTERNAL_EXPORT tlbfReturn tlbfPbrainStartProc(tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfPbrainEndProc  (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfPbrainCallProc (tlbfContext* context);

typedef struct _tlbfPbrainProc
{
    tlbfExtData m_Header;
    tlbfInstruction m_Start;
} tlbfPbrainProc;

typedef struct _tlbfPbrainCallstack
{
    tlbfExtData m_Header;
    tlbfInstruction m_ReturnInstruction;
} tlbfPbrainCallstack;

#endif/*__TLBF_PBRAIN_H__*/
