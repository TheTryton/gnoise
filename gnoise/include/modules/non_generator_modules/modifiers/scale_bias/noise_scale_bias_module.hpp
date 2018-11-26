#pragma once

#include "../noise_modifier_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_scale = 1.0f;
inline constexpr float default_bias = 0.0f;

class noise_scale_bias_module;

struct scale_bias
{
    inline static float apply(const noise_scale_bias_module* module, float x);
};

class noise_scale_bias_module : public noise_modifier_module_base<1, scale_bias, noise_scale_bias_module>
{
public:
    noise_scale_bias_module() noexcept = default;
public:
    inline float                                    scale() const
    {
        return _scale;
    }
    inline float                                    bias() const
    {
        return _bias;
    }
    void                                            set_scale(float scale);
    void                                            set_bias(float bias);
private:
    float                                           _scale = default_scale;
    float                                           _bias = default_bias;
};

inline float scale_bias::apply(const noise_scale_bias_module * module, float x)
{
    return x * module->scale() + module->bias();
}

GNOISE_NAMESPACE_END