#pragma once
#ifndef __TLBF_H__
#define __TLBF_H__
#ifdef __cplusplus
extern "C" {
#endif/*__cplusplus*/

#ifdef TLBF_DYNAMIC
# ifdef WIN32
#  ifdef TLBF_BUILD
#   define TLBF_EXPORT __declspec( dllexport )
#  else
#   define TLBF_EXPORT __declspec( dllimport )
#  endif
# endif
#endif
 
#ifndef TLBF_EXPORT
# define TLBF_EXPORT
#endif

typedef int tlbfReturn;
typedef char tlbfCell;
typedef const char* tlbfProgram;

typedef struct _tlbfContext tlbfContext;

#define TLBF_SUCCESS           0
#define TLBF_NO_CONTEXT        1
#define TLBF_EOF               2
#define TLBF_OUT_OF_RANGE      3
#define TLBF_INVALID_INPUT     4
#define TLBF_LANGUAGE_MISMATCH 5
    
TLBF_EXPORT tlbfReturn   tlbfInitContext     (tlbfContext** context);
TLBF_EXPORT tlbfReturn   tlbfTerminateContext(tlbfContext** context);

TLBF_EXPORT tlbfReturn   tlbfSetProgram      (tlbfContext* context, tlbfProgram program);
TLBF_EXPORT tlbfReturn   tlbfRun             (tlbfContext* context);

TLBF_EXPORT const char*  tlbfError();

#include "tlbf_lang.h"

#ifdef __cplusplus
}
#endif/*__cplusplus*/
#endif/*__TLBF_H__*/
