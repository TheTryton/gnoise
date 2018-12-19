#pragma once

#include "../noise_selector_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_select_falloff = 0.0f;
inline constexpr float default_select_min = -1.0f;
inline constexpr float default_select_max = 1.0f;

class noise_select_module;

struct select
{
    inline static float map_cubic_scurve(float x)
    {
        return x * x * (3.0f - 2.0f * x);
    }

    inline static float interpolate_linear(float a, float b, float x)
    {
        return (1.0f - x)*a + x * b;
    }

    inline static float apply(const noise_select_module* module, float c, float f, float s);
};

class noise_select_module : public noise_selector_module_base<3, select, noise_select_module>
{
public:
    noise_select_module() noexcept = default;
public:
    inline float                                    falloff() const
    {
        return _falloff;
    }
    inline float                                    min() const
    {
        return _min;
    }
    inline float                                    max() const
    {
        return _max;
    }
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

    void                                            set_falloff(float falloff);
    void                                            set_min(float min);
    void                                            set_max(float max);
    void                                            set_control_module(const noise_module* control_module);
    void                                            set_first_input_module(const noise_module* first_input_module);
    void                                            set_second_input_module(const noise_module* second_input_module);

    virtual float                                   compute(const vector1f& point) const override;
    virtual float                                   compute(const vector2f& point) const override;
    virtual float                                   compute(const vector3f& point) const override;
    virtual float                                   compute(const vector4f& point) const override;
private:
    bool                                            check_input_modules_validity() const;
private:
    float                                           _falloff = default_select_falloff;
    float                                           _min = default_select_min;
    float                                           _max = default_select_max;
};

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