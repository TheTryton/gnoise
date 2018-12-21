cmake_minimum_required(VERSION 3.8)
project(gnoise_preview)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(gnoise_preview_Sources
	main.cpp
    WND.hpp
    common.hpp

    models/module_models.hpp
    models/module_models.cpp

    delegates/additional_delegates.hpp
    delegates/additional_delegates.cpp

    flow_chart/flow_chart_common.hpp
    flow_chart/flow_chart_view_base.hpp
    flow_chart/flow_chart_view_base.cpp
    flow_chart/default_flow_chart_view.hpp
    flow_chart/default_flow_chart_view.cpp
    flow_chart/default_flow_chart_scene.hpp
    flow_chart/default_flow_chart_scene.cpp

    flow_chart/flow_chart_base/node_base.hpp
    flow_chart/flow_chart_base/node_base.cpp
    flow_chart/flow_chart_base/link_base.hpp
    flow_chart/flow_chart_base/link_base.cpp
    flow_chart/flow_chart_base/pin_base.hpp
    flow_chart/flow_chart_base/pin_base.cpp

    flow_chart/flow_chart_default/default_node.hpp
    flow_chart/flow_chart_default/default_node.cpp
    flow_chart/flow_chart_default/default_link.hpp
    flow_chart/flow_chart_default/default_link.cpp
    flow_chart/flow_chart_default/default_pin.hpp
    flow_chart/flow_chart_default/default_pin.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${gnoise_preview_Sources})

add_executable(gnoise_preview ${gnoise_preview_Sources})

target_link_libraries(gnoise_preview Qt5::Core Qt5::Gui Qt5::Widgets gnoise)
set_target_properties(gnoise_preview PROPERTIES CXX_STANDARD 17)
set_target_properties(gnoise_preview PROPERTIES LINKER_LANGUAGE CXX)