@echo off
setlocal enabledelayedexpansion

@REM call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"

set "PROJECT_DIR=%CD%"
set "BUILD_DIR=%PROJECT_DIR%\bin\build"
set "EXE_DIR=%PROJECT_DIR%\bin"

if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

cmake -S "%PROJECT_DIR%" -B "%BUILD_DIR%" ^
  -G "Ninja" ^
  "-DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%\scripts\buildsystems\vcpkg.cmake" ^
  "-DCMAKE_BUILD_TYPE=Release" ^
  

cmake --build "%BUILD_DIR%" --config Release
