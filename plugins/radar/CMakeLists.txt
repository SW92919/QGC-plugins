set(CMAKE_AUTOMOC ON)

set(RADAR_PLUGIN_SOURCES
    radar_plugin.cpp
    radar_plugin.h
    radar_widget.cpp
    radar_widget.h
    radar_entity.cpp
    radar_entity.h
)

set(RADAR_PLUGIN_QML
    radar_ui.qml
    RadarView.qml
    RadarEntity.qml
)

add_library(radar_plugin SHARED 
    ${RADAR_PLUGIN_SOURCES}
    # QML files are *not* sources for the C++ library build, do not include here
    #${RADAR_PLUGIN_QML}
)

# Enable AUTOMOC for this plugin
set_target_properties(radar_plugin PROPERTIES AUTOMOC ON PREFIX "" SUFFIX ".dll" OUTPUT_NAME "radar_plugin")


target_link_libraries(radar_plugin
    device_plugin_framework
    Qt5::Core
    Qt5::Widgets
    Qt5::Quick
    Qt5::Qml
)

# Set plugin properties
set_target_properties(radar_plugin PROPERTIES
    PREFIX ""
    SUFFIX ".dll"
    OUTPUT_NAME "radar_plugin"
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/plugins
)

# Copy QML files to output
foreach(QML_FILE ${RADAR_PLUGIN_QML})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${QML_FILE}")
        file(COPY "${QML_FILE}" DESTINATION ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})
    else()
        message(WARNING "QML file ${QML_FILE} does not exist in ${CMAKE_CURRENT_SOURCE_DIR}")
    endif()
endforeach()
#foreach(QML_FILE ${RADAR_PLUGIN_QML})
#    configure_file(${QML_FILE} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${QML_FILE} COPYONLY)
#endforeach()

# Install plugin
install(TARGETS radar_plugin
    DESTINATION plugins
)

# Install QML files (installation step will not fail if files are missing, but warns)
foreach(QML_FILE ${RADAR_PLUGIN_QML})
    if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${QML_FILE}")
        install(FILES "${QML_FILE}" DESTINATION plugins)
    endif()
endforeach()
