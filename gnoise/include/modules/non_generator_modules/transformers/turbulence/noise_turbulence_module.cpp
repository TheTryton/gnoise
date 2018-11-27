#include "noise_turbulence_module.hpp"
#include "..\linear_transformer\rotate_point\noise_rotate_point_module.hpp"

GNOISE_NAMESPACE_BEGIN

void noise_turbulence_module::set_power(float power)
{
    _power = power;
}

void noise_turbulence_module::set_computation_module(const noise_module* computation)
{
    set_input_module(0, computation);
}

void noise_turbulence_module::set_x_turbulence_module(const noise_module* turbulence_x)
{
    set_input_module(1, turbulence_x);
}

void noise_turbulence_module::set_y_turbulence_module(const noise_module* turbulence_y)
{
    set_input_module(2, turbulence_y);
}

void noise_turbulence_module::set_z_turbulence_module(const noise_module* turbulence_z)
{
    set_input_module(3, turbulence_z);
}

void noise_turbulence_module::set_w_turbulence_module(const noise_module* turbulence_w)
{
    set_input_module(4, turbulence_w);
}

void noise_turbulence_module::on_configuration_changed()
{
}

GNOISE_NAMESPACE_END