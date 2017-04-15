#ifndef __TLBF_SYMBOL_H__
#define __TLBF_SYMBOL_H__
typedef tlbfReturn tlbfReturn_t;

typedef unsigned char tlbfSymbol;

typedef tlbfReturn_t(*tlbfGetSymbol)(tlbfContext*, tlbfSymbol*);

#define TLBF_SYMBOL_UNKNOWN        0x00

/******************************************************************/
/* Standard BF symbols                                            */
/******************************************************************/
#define TLBF_SYMBOL_INCREMENT_CELL 0x01
#define TLBF_SYMBOL_DECREMENT_CELL 0x02
#define TLBF_SYMBOL_INCREMENT_PTR  0x03
#define TLBF_SYMBOL_DECREMENT_PTR  0x04
#define TLBF_SYMBOL_LOOP_START     0x05
#define TLBF_SYMBOL_LOOP_END       0x06
#define TLBF_SYMBOL_INPUT          0x07
#define TLBF_SYMBOL_OUTPUT         0x08


/******************************************************************/
/* PBrain extension symbols                                       */
/******************************************************************/
#define TLBF_SYMBOL_START_PROC     0x09
#define TLBF_SYMBOL_END_PROC       0x0A
#define TLBF_SYMBOL_CALL_PROC      0x0B

#define TLBF_SYMBOL_EOF            0xFF

#endif/*__TLBF_SYMBOL_H__*/
