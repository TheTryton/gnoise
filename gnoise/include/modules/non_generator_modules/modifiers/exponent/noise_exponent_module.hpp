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
    inline float                                    exponent() const
    {
        return _exponent;
    }
    void                                            set_exponent(float exponent);
private:
    float                                           _exponent = default_exponent;
};

inline float exponent::apply(const noise_exponent_module * module, float x)
{
    return std::pow(x, module->exponent());
}

GNOISE_NAMESPACE_END