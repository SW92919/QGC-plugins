# tests/
# ├── test_main.cpp                   # Main entry point for Qt Test application
# ├── test_plugin_load.cpp            # Basic plugin discovery test (your existing file)
# ├── test_plugin_manager.cpp         # Plugin manager lifecycle tests
# ├── test_mavlink_handler.cpp        # MAVLink communication tests
# ├── test_plugin_framework.cpp       # Comprehensive framework tests
# └── CMakeLists.txt                  # Build configuration for all tests


# Enable testing
enable_testing()
set(CMAKE_AUTOMOC ON)

# Find Qt Test Module
find_package(Qt5 REQUIRED COMPONENTS Test)

# Test executable
set(TEST_SOURCES
    test_main.cpp
    test_plugin_framework.cpp
    test_plugin_manager.cpp
    test_mavlink_handler.cpp
)

# Create test executable
add_executable(plugin_tests ${TEST_SOURCES})

# Enable AUTOMOC for tests
set_target_properties(plugin_tests PROPERTIES AUTOMOC ON
    # RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bins
)

# Ensure device_plugin_framework is built first
add_dependencies(plugin_tests device_plugin_framework)

# Link libraries - ensure device_plugin_framework is built first
target_link_libraries(plugin_tests
    device_plugin_framework
    Qt5::Core
    Qt5::Test
)

# Add test to CTest
add_test(NAME PluginFrameworkTests COMMAND plugin_tests)
# add_test(NAME BasicPluginLoadTest COMMAND plugin_tests --test-basic-load)
# add_test(NAME ManagerTests COMMAND plugin_tests --test-manager)
# add_test(NAME MAVLinkTests COMMAND plugin_tests --test-mavlink)

