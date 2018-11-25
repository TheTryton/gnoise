#include "noise_exponent_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline float exponent::apply(const noise_exponent_module* module, float x)
{
    return std::pow(module->exponent(), x);
}

inline float noise_exponent_module::exponent() const
{
    return _exponent;
}

void noise_exponent_module::set_exponent(float exponent)
{
    _exponent = exponent;
}

GNOISE_NAMESPACE_END