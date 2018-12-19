#include "noise_select_module.hpp"

GNOISE_NAMESPACE_BEGIN

void noise_select_module::set_falloff(float falloff)
{
    _falloff = falloff;
}

void noise_select_module::set_min(float min)
{
    _min = min;
}

void noise_select_module::set_max(float max)
{
    _max = max;
}

void noise_select_module::set_control_module(const noise_module* control_module)
{
    set_input_module(0, control_module);
}

void noise_select_module::set_first_input_module(const noise_module* first_input_module)
{
    set_input_module(1, first_input_module);
}

void noise_select_module::set_second_input_module(const noise_module* second_input_module)
{
    set_input_module(2, second_input_module);
}

GNOISE_NAMESPACE_END