@echo off
echo Cleaning build directories...

if exist build (
    echo Removing build directory...
    rmdir /s /q build
)

if exist build-debug (
    echo Removing build-debug directory...
    rmdir /s /q build-debug
)

if exist install (
    echo Removing install directory...
    rmdir /s /q install
)

echo Cleanup completed.
pause
