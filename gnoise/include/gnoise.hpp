#pragma once

//generators
#include "modules/generators/noise_generator_module.hpp"
#include "modules/generators/perlin/noise_perlin_generator_module.hpp"
#include "modules/generators/billow/noise_billow_generator_module.hpp"
#include "modules/generators/ridged_multifractal/noise_ridged_multifractal_generator_module.hpp"
#include "modules/generators/voronoi/noise_voronoi_generator_module.hpp"
#include "modules/generators/const/noise_const_generator_module.hpp"
#include "modules/generators/checkerboard/noise_checkerboard_generator_module.hpp"
#include "modules/generators/cylinders/noise_cylinders_generator_module.hpp"
#include "modules/generators/spheres/noise_spheres_generator_module.hpp"

//non_generators

//combiners
#include "modules/non_generator_modules/combiners/noise_combiner_module.hpp"

//modifiers
#include "modules/non_generator_modules/modifiers/noise_modifier_module.hpp"
#include "modules/non_generator_modules/modifiers/base/noise_base_module.hpp"
#include "modules/non_generator_modules/modifiers/clamp/noise_clamp_module.hpp"
#include "modules/non_generator_modules/modifiers/exponent/noise_exponent_module.hpp"
#include "modules/non_generator_modules/modifiers/scale_bias/noise_scale_bias_module.hpp"

//selectors
#include "modules/non_generator_modules/selectors/noise_selector_module.hpp"
#include "modules/non_generator_modules/selectors/blend/noise_blend_module.hpp"
#include "modules/non_generator_modules/selectors/select/noise_select_module.hpp"

//transformers
#include "modules/non_generator_modules/transformers/turbulence/noise_turbulence_module.hpp"
#include "modules/non_generator_modules/transformers/displace/noise_displace_module.hpp"
#include "modules/non_generator_modules/transformers/linear_transformer/translate_point/noise_translate_point_module.hpp"
#include "modules/non_generator_modules/transformers/linear_transformer/rotate_point/noise_rotate_point_module.hpp"
#include "modules/non_generator_modules/transformers/linear_transformer/scale_point/noise_scale_point_module.hpp"

//miscellaneous
#include "modules/non_generator_modules/miscellaneous/noise_miscellaneous_module.hpp"

//other
#include "modules/non_generator_modules/other/noise_other_module.hpp"