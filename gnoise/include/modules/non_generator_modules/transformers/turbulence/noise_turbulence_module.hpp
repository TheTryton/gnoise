#pragma once

#include "../noise_transformer_module.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_turbulence_module;

inline constexpr float default_turbulence_power = 1.0f;

struct turbulence
{
    template<unsigned int D>
    inline static void transform(const noise_turbulence_module* module, vectorf<D>& point, const array<float, D>& transformation);
};

class noise_turbulence_module : public noise_transformer_module_base_def_impl<5, turbulence, noise_turbulence_module>
{
public:
    noise_turbulence_module() noexcept = default;
public:
    inline float                                    power() const
    {
        return _power;
    }
    void                                            set_power(float power);

    inline const noise_module*                      computation_module() const
    {
        return input_module(0);
    }
    inline const noise_module*                      x_turbulence_module() const
    {
        return input_module(1);
    }
    inline const noise_module*                      y_turbulence_module() const
    {
        return input_module(2);
    }
    inline const noise_module*                      z_turbulence_module() const
    {
        return input_module(3);
    }
    inline const noise_module*                      w_turbulence_module() const
    {
        return input_module(4);
    }

    void                                            set_computation_module(const noise_module* computation);
    void                                            set_x_turbulence_module(const noise_module* turbulence_x);
    void                                            set_y_turbulence_module(const noise_module* turbulence_y);
    void                                            set_z_turbulence_module(const noise_module* turbulence_z);
    void                                            set_w_turbulence_module(const noise_module* turbulence_w);
protected:
    virtual void                                    on_configuration_changed() override;
private:
    float                                           _power = default_turbulence_power;
};

template<unsigned int D>
inline void turbulence::transform(const noise_turbulence_module* module, vectorf<D>& point, const array<float, D>& transformation)
{
    transformer_utility::element_wise_transform(point.coords, point.coords + D, [&module](float v, float disp) { return v + disp*module->power(); }, point.coords, transformation.begin());
}

GNOISE_NAMESPACE_END