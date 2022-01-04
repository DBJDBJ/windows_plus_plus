
## This is an attempt in refactoring ["Windows++"](https://web.archive.org/web/20090606220454/http://www.dilascia.com/wpp.htm) by [Paul Di Lascia](https://en.wikipedia.org/wiki/Paul_DiLascia)


#### Strategy

1. We will not use the make files, only Visual Studio solution and projects
1. Paul has originally built a DLL. 
   1. In 2021 we know for various good reasons C++ and DLL's don't work well together.
2. First attempt will consist of creating Visual Studio (VS) projects; one for each sample.
   1. Each VS project will be simple Windows App.
   2. Where the framework code will be included as code. 
3. Second cycle will be refactoring the framework into headers only
   1. Then using those headers into samples


---
Started 2022 January 4, by dbj at dbj dot org