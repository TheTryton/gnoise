#include "noise_cylinders_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

void noise_cylinders_generator_module::set_frequency(float frequency)
{
    _frequency = frequency;
}

void noise_cylinders_generator_module::on_configuration_changed()
{
    //TODO
}

GNOISE_NAMESPACE_END