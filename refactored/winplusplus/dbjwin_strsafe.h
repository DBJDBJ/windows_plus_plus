#pragma once
/*
 (c) 2020 - 2022 by dbj@dbj.org -- LICENSE_DBJ

 "normalization" of "crazy camel" strsafe.h function names

 ps: I do sincerely hope ucrt is not used to implement win32 strsafe 
     implementations are all inline and available to review
*/
#include <strsafe.h>

//STRSAFEAPI StringCchLengthA([in] STRSAFE_PCNZCH psz, [in] size_t cchMax,
//                            [out] size_t *pcchLength);
// that is used to check if the lenght of the string is smaller or equalt to a limit
// if it is S_OK is returned

#undef dbjwin_strlena
#define dbjwin_strlena StringCchLengthA

#undef dbjwin_strlenw
#define dbjwin_strlenw StringCchLengthW

/*

STRSAFEAPI StringCchPrintfA(  STRSAFE_LPSTR  pszDest,  size_t cchDest,  STRSAFE_LPCSTR pszFormat,  ...);

*/
#undef dbjwin_sprintfa
#define dbjwin_sprintfa StringCchPrintfA

#undef dbjwin_sprintfw
#define dbjwin_sprintfw StringCchPrintfW


// https://docs.microsoft.com/en-us/windows/win32/api/strsafe/nf-strsafe-stringcchvprintfa
/*

STRSAFEAPI StringCchVPrintfA(
  STRSAFE_LPSTR  pszDest,
  size_t         cchDest,
  STRSAFE_LPCSTR pszFormat,
  va_list        argList
);

*/
#undef dbjwin_vsprintfa
#define dbjwin_vsprintfa StringCchVPrintfA 

#undef dbjwin_vsprintfw
#define dbjwin_vsprintfw StringCchVPrintfW

//STRSAFEAPI StringCchCopyNA([out] STRSAFE_LPSTR pszDest, [in] size_t cchDest,
//                           [in] STRSAFE_PCNZCH pszSrc, [in] size_t cchToCopy);
#undef dbjwin_strncpya
#define dbjwin_strncpya StringCchCopyNA

#undef dbjwin_strncpyw
#define dbjwin_strncpyw StringCchCopyNW
