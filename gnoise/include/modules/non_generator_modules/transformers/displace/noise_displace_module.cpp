#include "noise_displace_module.hpp"

GNOISE_NAMESPACE_BEGIN

void noise_displace_module::set_computation_module(const noise_module * computation)
{
    set_input_module(0, computation);
}

void noise_displace_module::set_x_displace_module(const noise_module * displace_x)
{
    set_input_module(1, displace_x);
}

void noise_displace_module::set_y_displace_module(const noise_module * displace_y)
{
    set_input_module(2, displace_y);
}

void noise_displace_module::set_z_displace_module(const noise_module * displace_z)
{
    set_input_module(3, displace_z);
}

void noise_displace_module::set_w_displace_module(const noise_module * displace_w)
{
    set_input_module(4, displace_w);
}

void noise_displace_module::on_configuration_changed()
{
}

GNOISE_NAMESPACE_END