#ifndef __TLBF_LANG_H__
#define __TLBF_LANG_H__

#ifndef __TLBF_H__
#  error "tlbf_lang.h should not be included manually, it is included from tlbf.h"
#endif /*__TLBF_H__*/

typedef unsigned char tlbfLangFlags;

#define TLBF_LANG_BF    0x01
#define TLBF_LANG_FF    0x02
#define TLBF_LANG_OOK   0x03

#define TLBF_EXT_PBRAIN 0x10

TLBF_EXPORT tlbfReturn tlbfSetLangFlags(tlbfContext* context, tlbfLangFlags flags);

#endif/*__TLBF_LANG_H__*/
