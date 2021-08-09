/***
*mbsicoll.c - Collate MBCS strings, ignoring case
*
*       Copyright (c) Microsoft Corporation. All rights reserved.
*
*Purpose:
*       Collate MBCS strings, ignoring case
*
*******************************************************************************/
#ifndef _MBCS
    #error This file should only be compiled with _MBCS defined
#endif

#include <corecrt_internal.h>
#include <corecrt_internal_mbstring.h>
#include <locale.h>
#include <winapi_thunks.h>

/***
* _mbsicoll - Collate MBCS strings, ignoring case
*
*Purpose:
*       Collates two strings for lexical order (ignoring case).
*       Strings are collated on a character basis, not a byte basis.
*
*Entry:
*       char *s1, *s2 = strings to collate
*
*Exit:
*       Returns <0 if s1 < s2
*       Returns  0 if s1 == s2
*       Returns >0 if s1 > s2
*       Returns _NLSCMPERROR is something went wrong
*
*Exceptions:
*       Input parameters are validated. Refer to the validation section of the function.
*
*******************************************************************************/

#if _CRT_NTDDI_MIN < 0x06000000
extern "C" int __cdecl _mbsicoll_l(
        const unsigned char *s1,
        const unsigned char *s2,
        _locale_t plocinfo
        )
{
		if(!plocinfo)
			return _mbsicoll(s1, s2);

        int ret;
        //_LocaleUpdate _loc_update(plocinfo);

        /* validation section */
        _VALIDATE_RETURN(s1 != nullptr, EINVAL, _NLSCMPERROR);
        _VALIDATE_RETURN(s2 != nullptr, EINVAL, _NLSCMPERROR);

        if (plocinfo->mbcinfo->ismbcodepage == 0)
            return _stricoll_l((const char *)s1, (const char *)s2, plocinfo);

        if ( 0 == (ret = __acrt_CompareStringA(
                        plocinfo,
                        plocinfo->mbcinfo->mblcid,
                        SORT_STRINGSORT | NORM_IGNORECASE,
                        (LPCSTR)s1,
                        -1,
                        (LPSTR)s2,
                        -1,
                        plocinfo->mbcinfo->mbcodepage )) )
        {
            errno = EINVAL;
            return _NLSCMPERROR;
        }

        return ret - 2;

}
#endif

#if 0
extern "C" int (__cdecl _mbsicoll)(
        const unsigned char *s1,
        const unsigned char *s2
        )
{
    return _mbsicoll_l(s1, s2, nullptr);
}
#endif
