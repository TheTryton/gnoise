#include "noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

gnoise::module_type noise_generator_module::module_type() const
{
    return gnoise::module_type::generator;
}

GNOISE_NAMESPACE_END