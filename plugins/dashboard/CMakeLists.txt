set(DASHBOARD_PLUGIN_SOURCES
    DashboardPlugin.cpp
    DashboardPlugin.h
)

add_library(dashboard_plugin SHARED
    ${DASHBOARD_PLUGIN_SOURCES}
)

target_link_libraries)(dashboard_plugin
    device_plugin_framework
    Qt5::Core
    Qt5::Widgets
)

#Install the plugin

install(TARGETS dashboard_plugin
    DESTINATION plugins
)

install(FILES dashboard_plugin.json
    DESTINATION plugins
)
