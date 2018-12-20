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

    node_editor/node_model/model_common.hpp
    node_editor/node_model/node.hpp
    node_editor/node_model/node.cpp
    node_editor/node_model/link.hpp
    node_editor/node_model/link.cpp
    node_editor/node_model/pin.hpp
    node_editor/node_model/pin.cpp

    node_editor_scene/node_editor_scene.hpp
    node_editor_scene/node_editor_scene.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${gnoise_preview_Sources})

add_executable(gnoise_preview ${gnoise_preview_Sources})

target_link_libraries(gnoise_preview Qt5::Core Qt5::Gui Qt5::Widgets gnoise)
set_target_properties(gnoise_preview PROPERTIES CXX_STANDARD 17)
set_target_properties(gnoise_preview PROPERTIES LINKER_LANGUAGE CXX)