#include "noise_translate_point_module.hpp"

GNOISE_NAMESPACE_BEGIN

void noise_translate_point_module::set_translation_x(float translation_x)
{
    _translation[0] = translation_x;
}

void noise_translate_point_module::set_translation_y(float translation_y)
{
    _translation[1] = translation_y;
}

void noise_translate_point_module::set_translation_z(float translation_z)
{
    _translation[2] = translation_z;
}

void noise_translate_point_module::set_translation_w(float translation_w)
{
    _translation[3] = translation_w;
}

void noise_translate_point_module::on_configuration_changed()
{
}

GNOISE_NAMESPACE_END
