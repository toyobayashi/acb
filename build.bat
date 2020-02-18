@echo off

if not exist .\build\win32 mkdir .\build\win32
cmake -DACB_BUILD_DLL=true -A Win32 -S . -B .\build\win32
cmake --build .\build\win32 --config %1%

copy /Y .\test\*.acb .\build\win32\%1%\*.acb
copy /Y .\test\*.awb .\build\win32\%1%\*.awb
