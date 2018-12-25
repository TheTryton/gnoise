#include "noise_clamp_module.hpp"

GNOISE_NAMESPACE_BEGIN

void noise_clamp_module::set_lower_bound(float lower_bound)
{
    _lower_bound = lower_bound;
}

void noise_clamp_module::set_upper_bound(float upper_bound)
{
    _upper_bound = upper_bound;
}

GNOISE_NAMESPACE_END