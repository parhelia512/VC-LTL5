//
// lfind_s.cpp
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// Defines _lfind_s(), which performs a linear search over an array.
//
#ifdef __USE_CONTEXT
    #error __USE_CONTEXT should be undefined
#endif

#define __USE_CONTEXT
#if _CRT_NTDDI_MIN < 0x06000000
#include "lfind.cpp"
#endif
