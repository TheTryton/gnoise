#pragma once

#include "../noise_modifier_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_clamp_lower_bound = 0.0f;
inline constexpr float default_clamp_upper_bound = 0.0f;

class noise_clamp_module;

struct clamp
{
    inline static float apply(const noise_clamp_module* module, float x);
};

class noise_clamp_module : public noise_modifier_module_base<1, clamp, noise_clamp_module>
{
public:
    noise_clamp_module() noexcept = default;
public:
    inline float                                    lower_bound() const
    {
        return _lower_bound;
    }
    inline float                                    upper_bound() const
    {
        return _upper_bound;
    }
    void                                            set_lower_bound(float lower_bound);
    void                                            set_upper_bound(float upper_bound);
private:
    float                                           _lower_bound = default_clamp_lower_bound;
    float                                           _upper_bound = default_clamp_upper_bound;
};

inline float clamp::apply(const noise_clamp_module* module, float x)
{
    return std::max(module->lower_bound(), std::min(x, module->upper_bound()));
}

GNOISE_NAMESPACE_END