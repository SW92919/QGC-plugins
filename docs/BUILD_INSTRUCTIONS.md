# Build Instructions

## Prerequisites

### Required Software
- **Qt 5.12+** (Qt 5.15 recommended)
- **CMake 3.15+**
- **C++ Compiler**: MSVC 2019+, GCC 9+, or Clang 10+
    - Windows: MSVC 2019+ or MinGW
    - Linux: GCC 9+ or Clang 10+
    - macOS: Xcode 11+
    
### Qt Installation
1. Download Qt from https://www.qt.io/download
2. Install Qt5 Core, Widgets, Network, and Test modules
3. Ensure `qmake` is in your PATH

## Building the Framework

### 1. Clone Repository


    `git clone <your-repo-url>`
    
    `cd device-plugin-framework`


### 2. Create Build Directory


    `mkdir build`
    
    `cd build`


### 3. Configure with CMake


Debug build:
`cmake .. -DCMAKE_BUILD_TYPE=Debug`

Release build:
`cmake .. -DCMAKE_BUILD_TYPE=Release`

Specify Qt installation (if needed):
`cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/5.15.2/gcc_64`


### 4. Build

Build all targets:
`cmake --build .`

Build specific target:
`cmake --build . --target device_plugin_framework`

Parallel build (faster):
`cmake --build . -j 4`


## Expected Build Output

After successful build, you should have:

    build/
    ├── bin/
    │ ├── device_plugin_framework.dll (Windows) / .so (Linux)
    │ └── plugin_tests.exe
    ├── lib/
    │ └── device_plugin_framework.lib (Windows import library)
    └── plugins/
    ├── radar_plugin.dll
    ├── dashboard_plugin.dll
    └── my_example_plugin.dll (if built)

## Running Tests

### Unit Tests


Run all tests:  `./bin/plugin_tests`
    
Expected output should show all tests passing


### Manual Testing

Test plugin loading:
`./bin/plugin_tests --test-plugin-loading`

Test version compatibility:
`./bin/plugin_tests --test-version-compatibility`

## Integration with QGroundControl

### 1. Copy Framework Library

Copy to QGC installation directory:
`cp build/bin/device_plugin_framework.dll /path/to/QGC/`

Copy plugins:
`cp build/plugins/*.dll /path/to/QGC/plugins/`

### 2. Verify Integration
1. Start QGroundControl
2. Check console output for plugin loading messages
3. Verify no crashes during startup

## Troubleshooting

### Common Build Issues

**Qt not found:**

`cmake .. -DCMAKE_PREFIX_PATH=/path/to/Qt/5.15.2/[compiler]`

**Compiler not found (Windows):**

Use Visual Studio Developer Command Prompt

Or specify generator:
`cmake .. -G "Visual Studio 16 2019"`

**Missing moc files:**
- Ensure `set(CMAKE_AUTOMOC ON)` is set
- Clean build directory and rebuild

**Linker errors:**
- Check that all source files are listed in CMakeLists.txt
- Verify Qt modules are properly linked
- Ensure consistent Debug/Release configuration

### Build Configurations

**Debug Build:**
- Includes debug symbols
- Enables assertions and debug logging
- Slower execution, larger binaries

**Release Build:**
- Optimized for performance
- Minimal debug information
- Recommended for production use

## IDE Support

### Qt Creator
1. Open `CMakeLists.txt` as project
2. Configure build directory
3. Build and run directly from IDE

### Visual Studio (Windows)
1. Generate VS solution: `cmake .. -G "Visual Studio 16 2019"`
2. Open `device-plugin-framework.sln`
3. Build from Visual Studio

### CLion
1. Open project directory
2. CLion automatically detects CMake configuration
3. Build and debug from IDE
