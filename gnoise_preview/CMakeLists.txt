cmake_minimum_required(VERSION 3.8)
project(gnoise_preview)

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

set(gnoise_preview_Sources
	main.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${gnoise_preview_Sources})

add_executable(gnoise_preview ${gnoise_preview_Sources})

target_link_libraries(gnoise_preview Qt5::Core Qt5::Gui Qt5::Widgets gnoise)

set_target_properties(gnoise_preview PROPERTIES CXX_STANDARD 17)
set_target_properties(gnoise_preview PROPERTIES LINKER_LANGUAGE CXX)