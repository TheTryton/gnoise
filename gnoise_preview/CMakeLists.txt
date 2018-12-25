cmake_minimum_required(VERSION 3.8)
project(gnoise_preview)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(gnoise_preview_Sources
	main.cpp

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

    preview_flow_chart/preview_common.hpp

    preview_flow_chart/preview_base/preview_node_base.hpp
    preview_flow_chart/preview_base/preview_node_base.cpp
    preview_flow_chart/preview_base/preview_pin_base.hpp
    preview_flow_chart/preview_base/preview_pin_base.cpp
    preview_flow_chart/preview_base/preview_node_title.hpp
    preview_flow_chart/preview_base/preview_node_title.cpp

    preview_flow_chart/module_data/module_data.hpp
    preview_flow_chart/module_data/module_data.cpp

    preview_flow_chart/module_model/module_model.hpp
    preview_flow_chart/module_model/module_model.cpp

    preview_flow_chart/module_nodes/module_nodes.hpp

    preview_flow_chart/result_node/result_node.hpp
    preview_flow_chart/result_node/result_node.cpp
    preview_flow_chart/result_node/result_node_image.hpp
    preview_flow_chart/result_node/result_node_image.cpp

    preview_flow_chart/view/preview_flow_chart_view.hpp
    preview_flow_chart/view/preview_flow_chart_view.cpp

    preview_flow_chart/widget/preview_widget.hpp
    preview_flow_chart/widget/preview_widget.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${gnoise_preview_Sources})

add_executable(gnoise_preview ${gnoise_preview_Sources})

target_link_libraries(gnoise_preview Qt5::Core Qt5::Gui Qt5::Widgets gnoise)
set_target_properties(gnoise_preview PROPERTIES CXX_STANDARD 17)
set_target_properties(gnoise_preview PROPERTIES LINKER_LANGUAGE CXX)