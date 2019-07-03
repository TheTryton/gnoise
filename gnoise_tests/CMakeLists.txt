cmake_minimum_required(VERSION 3.8)
project(gnoise_tests)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

set(gnoise_tests_Sources
	main.cpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${gnoise_tests_Sources})

enable_testing()

add_executable(gnoise_tests ${gnoise_tests_Sources})

include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(gnoise_tests PRIVATE gnoise ${Boost_LIBRARIES})

set_target_properties(gnoise_tests PROPERTIES CXX_STANDARD 17)
set_target_properties(gnoise_tests PROPERTIES LINKER_LANGUAGE CXX)