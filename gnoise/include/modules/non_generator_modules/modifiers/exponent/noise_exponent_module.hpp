#pragma once

#include "../noise_modifier_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_exponent = 2.0f;

class noise_exponent_module;

struct exponent
{
    inline static float apply(const noise_exponent_module* module, float x);
};

class noise_exponent_module : public noise_modifier_module_base<1, exponent, noise_exponent_module>
{
public:
    noise_exponent_module() noexcept = default;
public:
    inline float                                    exponent() const;
    void                                            set_exponent(float exponent);
private:
    float                                           _exponent = default_exponent;
};

GNOISE_NAMESPACE_END