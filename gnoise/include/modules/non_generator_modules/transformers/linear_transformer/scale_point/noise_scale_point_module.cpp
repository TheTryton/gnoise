#include "noise_scale_point_module.hpp"

GNOISE_NAMESPACE_BEGIN

void noise_scale_point_module::set_scale_x(float scale_x)
{
    _scale[0] = scale_x;
}

void noise_scale_point_module::set_scale_y(float scale_y)
{
    _scale[1] = scale_y;
}

void noise_scale_point_module::set_scale_z(float scale_z)
{
    _scale[3] = scale_z;
}

void noise_scale_point_module::set_scale_w(float scale_w)
{
    _scale[3] = scale_w;
}

void noise_scale_point_module::on_configuration_changed()
{
}

GNOISE_NAMESPACE_END