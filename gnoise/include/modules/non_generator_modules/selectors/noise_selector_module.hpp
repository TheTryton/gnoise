#pragma once

#include "../noise_non_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

template<size_t I_C, class F, class D>
using noise_selector_module_base = noise_non_generator_module_def_impl<I_C, F, D, module_type::selector>;

GNOISE_NAMESPACE_END