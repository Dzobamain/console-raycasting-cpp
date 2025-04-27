@echo off
setlocal enabledelayedexpansion

set OUT=cr.exe

set SRC=

for /r %%f in (*.c) do (
    set "SRC=!SRC! %%f"
)

if "%SRC%"=="" (
    echo No .c files found.
    exit /b 1
)

gcc %SRC% -o %OUT%
if errorlevel 1 (
    echo ❌ Build failed.
    exit /b 1
)

echo ✅ Build complete. Executable is: %OUT%
pause