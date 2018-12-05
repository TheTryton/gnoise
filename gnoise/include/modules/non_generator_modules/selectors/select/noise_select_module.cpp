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

inline float select::apply(const noise_select_module * module, float c, float f, float s)
{
    float min = module->min();
    float max = module->max();
    float falloff = module->falloff();

    if (std::fabs(falloff) > std::numeric_limits<float>::epsilon())
    {
        float a;
        float lmn = min - falloff;
        if (c < lmn)
        {
            return f;
        }
        float umn = min + falloff;
        if (c < umn)
        {
            a = map_cubic_scurve((c - lmn) / (umn - lmn));
            return interpolate_linear(
                f,
                s,
                a
            );
        }
        float lmx = max - falloff;
        if (c < lmx)
        {
            return s;
        }
        float umx = max + falloff;
        if (c < umx)
        {
            a = map_cubic_scurve((c - lmn) / (umn - lmn));
            return interpolate_linear(
                s,
                f,
                a
            );
        }
        return f;
    }
    if (c < min)
    {
        return f;
    }
    if (c > max)
    {
        return s;
    }

    return f;
}

GNOISE_NAMESPACE_END