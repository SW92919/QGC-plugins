@echo off
echo Installing QGC Plugins...

if not exist build (
    echo Error: Build directory not found. Run build.bat first.
    pause
    exit /b 1
)

pushd build
cmake --install . --config Release --prefix ../install
popd

echo Installation completed in 'install' directory.
pause
