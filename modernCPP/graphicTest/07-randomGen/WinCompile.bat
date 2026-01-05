@echo off
REM Usage: WinCompile.bat source.cpp

if "%~1"=="" (
   echo Usage: WinCompile.bat source.cpp
   exit /b 1
)

call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars32.bat"

cl /std:c++17 /EHsc "%~1" ^ user32.lib gdi32.lib opengl32.lib winmm.lib kernel32.lib shell32.lib ole32.lib
