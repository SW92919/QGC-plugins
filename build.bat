@echo off
setlocal enabledelayedexpansion

echo ================================================
echo      QGC Plugins Build System
echo ================================================

:: Check if CMake is installed
where cmake >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake not found in PATH!
    echo Please install CMake and add to PATH
    pause
    exit /b 1
)

:: Check if Qt is available
where qmake >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo WARNING: Qt qmake not found in PATH
    echo Make sure Qt5 is properly installed
)

:: Create and enter build directory
if not exist build mkdir build
pushd build

:: Configure with CMake
echo Configuring project...
cmake .. -G "Visual Studio 17 2022" -A x64 ^
    -DCMAKE_BUILD_TYPE=Release ^
    -DQt5_DIR="C:\Qt\5.15.2\msvc2019_64\lib\cmake\Qt5"

if %ERRORLEVEL% neq 0 (
    echo ERROR: CMake configuration failed!
    popd
    pause
    exit /b 1
)

:: Build the project
echo Building project...
cmake --build . --config Release --parallel %NUMBER_OF_PROCESSORS%

if %ERRORLEVEL% neq 0 (
    echo ERROR: Build failed!
    popd
    pause
    exit /b 1
)

popd

echo.
echo ================================================
echo      Build completed successfully!
echo      Plugins location: build\plugins\
echo ================================================
pause
