cmake_minimum_required(VERSION 3.8)
project(gnoise)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

##gnoise
add_subdirectory(gnoise)
##gnoise_preview
add_subdirectory(gnoise_preview)