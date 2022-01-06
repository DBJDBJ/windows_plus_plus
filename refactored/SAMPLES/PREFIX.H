// 2022 Refactoring by dbj at dbj dot org
// yes, will put on the include path
#pragma once

// DBJ: we use clang_cl, thorugh Visual Studio 2019
// to compile this library
#ifdef __clang__
#pragma clang system_header
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wnonportable-include-path"
#endif  // __clang__



#include <winplusplus/WPP.H>

// DBJ WIN stuff
#include <winplusplus/dbjwin_strsafe.h>

