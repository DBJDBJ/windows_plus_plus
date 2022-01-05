
## This is an attempt in refactoring 1992 ["Windows++"](https://web.archive.org/web/20090606220454/http://www.dilascia.com/wpp.htm) by [Paul Di Lascia](https://en.wikipedia.org/wiki/Paul_DiLascia)

**What is built and ad-hoc tested to date (2022-01-05) is all in the sample folder:**

- samples
  - draw
  - hello 
  - launch
  - mandel
  - medit (has redraw issues)
  - memtest
  - mkc
  - people
  - randrect
  - toe
  - winedit

How does that look? Archaic. Is it working? Very much so. Simple, small and very functional Win32 C++ framework. Perfectly usable.

This is kind-of-a ["orthodox C++"](https://gist.github.com/bkaradzic/2e39896bc7d8c34e042b) in here. Although Orthodox C++ term was invented years (decades?) after Windows++. In here it is simply ancient C++. 

MS C/C++ 10.0 or greater is required. That is old.

In here there is also, no std lib whatsoever. No C++ exceptions.  C++ dialect in here is perhaps even predating C++03.

For refactoring we used C++14 (because that is Visual Studio 2019 default).

Win32 is used as much as possible. CRT and [UCRT](https://stackoverflow.com/questions/67848972/differences-between-msvcrt-ucrt-and-vcruntime-libraries) usage, will be eventually completely removed.


### Refactoring Strategy

1. Not using the make files, only Visual Studio solution and projects
1. Paul has originally built a DLL. 
   1. In 2021 we know for various good reasons C++ and DLL's don't work well together.
   2. thus a lib is made
2. First cycle consist of creating Visual Studio (VS) projects; one for each sample.
   1. Each VS project is simple Windows App.
   2. Framework is referenced (used) as a lib project
3. Second cycle will be refactoring the framework into headers only
   1. Then using those headers into samples
4. Minimize of completely remove UCRT usage
   1. `dbjwin_strsafe.h` is a step in that direction

### Usage

   1. Windows++ is built as a static lib
      1. named `winplusplus.lib`
      2. include as 
   ```cpp
   #include <winplusplus/wpp.h>
   // optional; if graphics++ are required
   #include <winplusplus/gpp.h>
   ```
   1. **Problem**: RC files do include `wpp.h` and `wprint.dlg` by using the relative path
      1. obviously `RC_INVOKED` parts will be taken out of `wpp.h`

### Details for the codenauts

Generally look into project properties. In particular:

1. "Windows++" was not UNICODE enabled. Every SAMPLES Project character set must be set to: "Not Set"
1. that is `_UNICODE` and `UNICODE` must be **undefined**
   2. for some reason `const` had not type e.g.: `const whatever = 42`
   1. I can not recall that was a legal C++ syntax in the past?
   2. so we changed all of them.


---
Started 2022 January 4, by dbj at dbj dot org