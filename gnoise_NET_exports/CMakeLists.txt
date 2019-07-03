cmake_minimum_required(VERSION 3.8)
project(gnoise_NET_exports)

set(gnoise_NET_exports_Sources
	exports.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${gnoise_NET_exports_Sources})

add_library(gnoise_NET_exports SHARED ${gnoise_NET_exports_Sources})

target_include_directories(gnoise_NET_exports PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gnoise_NET_exports gnoise)

set_target_properties(gnoise_NET_exports PROPERTIES CXX_STANDARD 17)
set_target_properties(gnoise_NET_exports PROPERTIES LINKER_LANGUAGE CXX)