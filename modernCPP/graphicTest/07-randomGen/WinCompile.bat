@echo off
REM Usage: WinCompile.bat source.cpp

if "%~1"=="" (
    echo Usage: WinCompile.bat source.cpp
    exit /b 1
)

REM === Try Visual Studio 2022 Community ===
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    echo Using Visual Studio 2022 Community
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars32.bat" (
    echo Using Visual Studio 2019 Professional
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Professional\VC\Auxiliary\Build\vcvars32.bat"
) else (
    echo ERROR: No supported Visual Studio installation found.
    exit /b 1
)

REM === Compile ===
cl /std:c++17 /EHsc "%~1" ^
    user32.lib gdi32.lib opengl32.lib winmm.lib kernel32.lib shell32.lib ole32.lib

@REM timeout /t 4 /nobreak

REM === Clean up Object files ===
DEL *.obj