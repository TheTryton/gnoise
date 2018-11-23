cmake_minimum_required(VERSION 3.8)
project(gnoise)

find_package(OpenCL REQUIRED)

set(gnoise_Sources
	main.cpp

	include/common.hpp

	include/modules/noise_module.hpp
	include/modules/noise_module.cpp

    include/modules/generators/noise_generator_module.hpp
    include/modules/generators/noise_generator_module.cpp

    include/modules/generators/const/noise_const_generator_module.hpp
    include/modules/generators/const/noise_const_generator_module.cpp

    include/modules/generators/perlin/noise_perlin_generator_module.hpp
    include/modules/generators/perlin/noise_perlin_generator_module.cpp

    include/modules/non_generator_modules/noise_non_generator_module.hpp
    include/modules/non_generator_modules/noise_non_generator_module.cpp

    include/modules/non_generator_modules/combiners/noise_combiner_module.hpp
    include/modules/non_generator_modules/miscellaneous/noise_miscellaneous_module.hpp
    include/modules/non_generator_modules/modifiers/noise_modifier_module.hpp
    include/modules/non_generator_modules/other/noise_other_module.hpp
    include/modules/non_generator_modules/selectors/noise_selector_module.hpp
    include/modules/non_generator_modules/transformers/noise_transformer_module.hpp
)

source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${gnoise_Sources})

add_library(gnoise STATIC ${gnoise_Sources})

target_include_directories(gnoise PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(gnoise OpenCL::OpenCL)

set_target_properties(gnoise PROPERTIES CXX_STANDARD 17)
set_target_properties(gnoise PROPERTIES LINKER_LANGUAGE CXX)