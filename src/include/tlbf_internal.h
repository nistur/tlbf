#pragma once
#ifndef __TLBF_INTERNAL_H__
#define __TLBF_INTERNAL_H__

#include "tlbf.h"
#define TLBF_EXPORT_INTERNALS
#ifdef TLBF_EXPORT_INTERNALS
# if __cplusplus
#  define TLBF_INTERNAL_EXPORT extern "C"
# endif
#endif

#ifndef TLBF_INTERNAL_EXPORT
# define TLBF_INTERNAL_EXPORT
#endif


#ifndef  TLBF_CELL_COUNT
# define TLBF_CELL_COUNT 30000
#endif /*TLBF_CELL_COUNT*/

#ifndef  TLBF_NEG_CELLS
# define TLBF_NEG_CELLS 100
#endif

#ifndef  TLBF_LOOP_COUNT
# define TLBF_LOOP_COUNT 40960
#endif /*TLBF_LOOP_COUNT*/

#ifndef TLBF_MAX_INSTRUCTIONS
# define TLBF_MAX_INSTRUCTIONS 16
#endif/*TLBF_MAX_INSTRUCTIONS*/

typedef const char* tlbfInstruction;
typedef tlbfReturn(*tlbfFunction)(tlbfContext*);
typedef int tlbfCellIndex;

typedef struct _tlbfLoopNode
{
    tlbfInstruction m_LoopStart;

    struct _tlbfLoopNode*  m_Next;
}tlbfLoopNode;

/***************************************
 * Library context
 * - holds current state
 ***************************************/
struct _tlbfContext
{
    tlbfCell        m_Cells               [TLBF_CELL_COUNT];
    tlbfCellIndex   m_CurrentCell;

    tlbfLoopNode*   m_LastLoopNode;
    tlbfLoopNode*   m_FreeLoopNode;

    tlbfProgram     m_Program;
    tlbfInstruction m_CurrentInstruction;

    tlbfLoopNode    m_LoopNodes           [TLBF_LOOP_COUNT];
    

    tlbfFunction    m_InstructionSet      [TLBF_MAX_INSTRUCTIONS];
    tlbfLangFlags   m_Flags;

    tlbfFunction    m_Next;
};

#define TLBF_NULL_CHECK(check, ret) \
    if(check == 0) tlbfReturnCode(ret) 

#define TLBF_CELL \
    (context->m_Cells[context->m_CurrentCell])

/***************************************
 * Some basic memory management wrappers
 ***************************************/
#include <stdlib.h>
#define tlbfMalloc(x) (x*)malloc(sizeof(x))
#define tlbfFree(x)   free(x)

/***************************************
 * Error handling
 ***************************************/
extern tlbfReturn  g_tlbfError;
extern const char* g_tlbfErrors[];
#define tlbfReturnCode(x)	       		\
    {						\
	g_tlbfError = TLBF_##x;			\
	return TLBF_##x;			\
    }
#define tlbfReturnCheck(x)			\
    {						\
	if(x != TLBF_SUCCESS)			\
	    return g_tlbfError;			\
    }
#define tlbfReturn()				\
    {						\
	return g_tlbfError;			\
    }

TLBF_INTERNAL_EXPORT tlbfReturn tlbfNext(tlbfContext* context);

#include "tlbf_symbol.h"
#include "tlbf_bf.h"
#include "tlbf_ook.h"

#endif/*__TLBF_INTERNAL_H__*/
