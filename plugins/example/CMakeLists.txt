set(CMAKE_AUTOMOC ON)

# Find required Qt modules
find_package(Qt5 REQUIRED COMPONENTS Core)

# Plugin source
set(PLUGIN_SOURCES
    my_example_plugin.cpp
    my_example_plugin.h
)

# Create plugin library
add_library(my_example_plugin SHARED ${PLUGIN_SOURCES})

# Set plugin properties
set_target_properties(my_example_plugin PROPERTIES
    AUTOMOC ON
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)

# Link to framework and Qt
target_link_libraries(my_example_plugin
    device_plugin_framework
    Qt5::Core
)

# Include framework headers
target_include_directories(my_example_plugin PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)
