# Device Plugin Framework for QGroundControl

A modular, extensible plugin architecture for QGroundControl 5.0+ that allows seamless integration of additional ground-based and aerial devices without modifying QGC's core codebase.

## Features

- **Plugin Interface**: Abstract base class for all device plugins
- **Dynamic Loading**: Runtime plugin discovery and lifecycle management
- **Version Compatibility**: Ensures compatibility with QGC 5.0+
- **MAVLink Integration**: Built-in MAVLink message parsing and entity detection
- **Modular Architecture**: Clean separation between framework and plugins

## Quick Start

1. Build the framework:

- mkdir build && cd build
- cmake ..
- cmake --build .

2. Run tests:

- ./bin/plugin_tests

3. Create your first plugin by following the [Plugin Development Guide](PLUGIN_DEVELOPMENT_GUIDE.md)

## Project Structure

    ├── src/ # Core framework library     
    ├── plugins/ # Plugin implementations     
    ├── tests/ # Unit and integration tests    
    └── docs/ # Documentation

## Requirements

- Qt 5.12+
- CMake 3.15+
- QGroundControl 5.0+
- C++14 compatible compiler

## License



