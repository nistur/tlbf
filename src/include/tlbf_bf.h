#ifndef __TLBF_BF_H__
#define __TLBF_BF_H__

TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfInit     (tlbfContext* context, tlbfGetSymbol* getSymbol);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfNext     (tlbfContext* context);

TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfIncrementCell(tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfDecrementCell(tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfIncrementPtr (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfDecrementPtr (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfLoopStart    (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfLoopEnd      (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfOutput       (tlbfContext* context);
TLBF_INTERNAL_EXPORT tlbfReturn tlbfBfInput        (tlbfContext* context);

#endif/*__TLBF_BF_H__*/
