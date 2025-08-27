cmake_minimum_required(VERSION 3.15)
project(QGCPlugins VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Find Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Quick Qml Network Test)

# Enable testing
enable_testing()

# Add subdirectories
# Build order matters - framework must be built before tests
add_subdirectory(src)
add_subdirectory(plugins)
add_subdirectory(tests)
add_subdirectory(plugins/example)

# QGC Integration (if qgroundcontrol folder exists)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/qgroundcontrol)
    set(QGC_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/qgroundcontrol)
    message(STATUS "Found QGroundControl at: ${QGC_ROOT}")
endif()
