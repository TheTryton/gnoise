#pragma once

#include "../noise_non_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

template<size_t I_C, class F, class D>
using noise_modifier_module_base = noise_non_generator_module_def_impl<I_C, F, D, module_type::modifier>;

//trivial modifiers

class noise_abs_module;

struct abs
{
    inline static float apply(const noise_abs_module* module, float a)
    {
        return std::abs(a);
    }
};

class noise_abs_module : public noise_modifier_module_base<1, abs, noise_abs_module> {};

GNOISE_NAMESPACE_END