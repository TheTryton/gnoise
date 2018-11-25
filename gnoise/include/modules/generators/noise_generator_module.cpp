#include "noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

gnoise::module_type noise_generator_module_base::module_type() const
{
    return module_type::generator;
}

GNOISE_NAMESPACE_END