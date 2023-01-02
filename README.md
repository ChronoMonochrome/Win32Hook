# Win32Hook

A simple hook for win32 applications.

This repository contains a program calling a function from dll.
We intercept the call, redirecting the execution to a function from an EXE instead.

The intended use is reverse-engineering a closed-source dll, as well as learning some hooking mechanisms in Windows.


# Build
```
cmake -DCMAKE_GENERATOR_PLATFORM=WIN32 .
msbuild dllproj.sln /t:build /p:Configuration=Release;Platform=WIN32
```
