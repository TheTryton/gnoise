#include "noise_scale_bias_module.hpp"

GNOISE_NAMESPACE_BEGIN

void noise_scale_bias_module::set_scale(float scale)
{
    _scale = scale;
}

void noise_scale_bias_module::set_bias(float bias)
{
    _bias = bias;
}

GNOISE_NAMESPACE_END