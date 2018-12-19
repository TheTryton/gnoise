#pragma once

#include "../noise_modifier_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_base = 2.0f;

class noise_base_module;

struct base
{
    inline static float apply(const noise_base_module* module, float x);
};

class noise_base_module : public noise_modifier_module_base<1, base, noise_base_module>
{
public:
    noise_base_module() noexcept = default;
public:
    inline float                                    base() const
    {
        return _base;
    }
    void                                            set_base(float base);
private:
    float                                           _base = default_base;
};

inline float base::apply(const noise_base_module * module, float x)
{
    return std::pow(x, module->base());
}

GNOISE_NAMESPACE_END