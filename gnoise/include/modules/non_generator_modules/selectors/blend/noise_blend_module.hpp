#pragma once

#include "../noise_selector_module.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_blend_module;

struct blend
{
    inline static float interpolate_linear(float a, float b, float x)
    {
        return (1.0f - x)*a + x * b;
    }

    inline static float apply(const noise_blend_module* module, float c, float f, float s)
    {
        return interpolate_linear(f, s, c);
    }
};

class noise_blend_module : public noise_selector_module_base<3, blend, noise_blend_module>
{
public:
    noise_blend_module() noexcept = default;
public:
    inline const noise_module*                      control_module() const
    {
        return input_module(0);
    }
    inline const noise_module*                      first_input_module() const
    {
        return input_module(1);
    }
    inline const noise_module*                      second_input_module() const
    {
        return input_module(2);
    }

    void                                            set_control_module(const noise_module* control_module);
    void                                            set_first_input_module(const noise_module* first_input_module);
    void                                            set_second_input_module(const noise_module* second_input_module);
};

GNOISE_NAMESPACE_END