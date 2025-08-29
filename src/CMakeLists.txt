# Device Plugin Framework Library
set(CMAKE_AUTOMOC ON)

# Optional: Define QGC version at build time
# These could be passed from parent CMake or detected from QGC build
set(QGC_VERSION_MAJOR 5 CACHE STRING "QGC Major Version")
set(QGC_VERSION_MINOR 0 CACHE STRING "QGC Minor Version")
set(QGC_VERSION_PATCH 0 CACHE STRING "QGC Patch Version")

# Add version definitions
add_definitions(
    -DQGC_VERSION_MAJOR=${QGC_VERSION_MAJOR}
    -DQGC_VERSION_MINOR=${QGC_VERSION_MINOR}
    -DQGC_VERSION_PATCH=${QGC_VERSION_PATCH}
)

set(FRAMEWORK_SOURCES
    device_plugin_interface.h
    device_plugin_manager.cpp
    device_plugin_manager.h
    mavlink_handler.cpp
    mavlink_handler.h
    mavlink_message_parser.h
    mavlink_message_parser.cpp
    version_compatibility.cpp
    version_compatibility.h
)

add_library(device_plugin_framework SHARED ${FRAMEWORK_SOURCES})

# Enable AUTOMOC for this target specifically
set_target_properties(device_plugin_framework PROPERTIES AUTOMOC ON
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

target_include_directories(device_plugin_framework PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(device_plugin_framework
    Qt5::Core
    Qt5::Widgets
    Qt5::Network
)

# Export symbols on Windows
if(WIN32)
  target_compile_definitions(device_plugin_framework PRIVATE FRAMEWORK_EXPORTS)
endif()

# Install framework
install(TARGETS device_plugin_framework
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION lib
)
