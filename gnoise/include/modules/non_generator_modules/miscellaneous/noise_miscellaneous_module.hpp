#pragma once

#include "../noise_non_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

template<size_t I_C, class F, class D>
using noise_miscellaneous_module_base = noise_non_generator_module_def_impl<I_C, F, D, module_type::miscellaneous>;

GNOISE_NAMESPACE_END