#pragma once
/*
 (c) 2020 - 2022 by dbj@dbj.org -- LICENSE_DBJ

 "normalization" of "crazy camel" strsafe.h function names

 ps: I do sincerely hope ucrt is not used to implement win32 strsafe 
*/
#include <strsafe.h>

// https://docs.microsoft.com/en-us/windows/win32/api/strsafe/nf-strsafe-stringcchprintfa
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

