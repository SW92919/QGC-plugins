@echo off
echo Building QGC Plugins (Debug Mode)...

if not exist build-debug mkdir build-debug
pushd build-debug

cmake .. -G "Visual Studio 17 2022" -A x64 ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DQt5_DIR="C:\Qt\5.15.2\msvc2019_64\lib\cmake\Qt5"

if %ERRORLEVEL% neq 0 (
    echo CMake configuration failed!
    popd
    pause
    exit /b 1
)

cmake --build . --config Debug --parallel %NUMBER_OF_PROCESSORS%

if %ERRORLEVEL% neq 0 (
    echo Debug build failed!
    popd
    pause
    exit /b 1
)

popd
echo Debug build completed!
pause
