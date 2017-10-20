#ifndef __TLBF_BF_H__
#define __TLBF_BF_H__

#define TLBF_BF_INCREMENT_CELL '+'
#define TLBF_BF_DECREMENT_CELL '-'
#define TLBF_BF_INCREMENT_PTR  '>'
#define TLBF_BF_DECREMENT_PTR  '<'
#define TLBF_BF_LOOP_START     '['
#define TLBF_BF_LOOP_END       ']'
#define TLBF_BF_INPUT          ','
#define TLBF_BF_OUTPUT         '.'

static const char tlbfBfCommands[] = 
{
    0xFF,
    TLBF_BF_INCREMENT_CELL,
    TLBF_BF_DECREMENT_CELL,
    TLBF_BF_INCREMENT_PTR,
    TLBF_BF_DECREMENT_PTR,
    TLBF_BF_LOOP_START,
    TLBF_BF_LOOP_END,
    TLBF_BF_INPUT,
    TLBF_BF_OUTPUT,
};


TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfInit     (tlbfContext* context, tlbfGetSymbol* getSymbol);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfNext     (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfGetSymbol(tlbfContext* context, tlbfSymbol* symbol);

TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfIncrementCell(tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfDecrementCell(tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfIncrementPtr (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfDecrementPtr (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfLoopStart    (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfLoopEnd      (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfOutput       (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfInput        (tlbfContext* context);

#endif/*__TLBF_BF_H__*/
