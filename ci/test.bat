@echo off
echo Running QGC Plugin Framework Tests...

if not exist build (
    echo Error: No build directory found. Run build.bat first.
    pause
    exit /b 1
)

pushd build

echo Running CTest...
ctest --output-on-failure --verbose
set TEST_RESULT=%ERRORLEVEL%


if %TEST_RESULT% neq 0 (
    echo Some tests failed!
    popd
    pause
    exit /b 1
)

echo All tests passed successfully!
popd
pause
