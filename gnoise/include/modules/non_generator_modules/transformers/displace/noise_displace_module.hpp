#pragma once

#include "../noise_transformer_module.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_displace_module;

struct displace
{
    template<unsigned int D>
    inline static void transform(const noise_displace_module* module, vectorf<D>& point, const array<float, D>& transformation);
};

class noise_displace_module : public noise_transformer_module_base_def_impl<5, displace, noise_displace_module>
{
public:
    noise_displace_module() noexcept = default;
public:
    inline const noise_module*                      computation_module() const
    {
        return input_module(0);
    }
    inline const noise_module*                      x_displace_module() const
    {
        return input_module(1);
    }
    inline const noise_module*                      y_displace_module() const
    {
        return input_module(2);
    }
    inline const noise_module*                      z_displace_module() const
    {
        return input_module(3);
    }
    inline const noise_module*                      w_displace_module() const
    {
        return input_module(4);
    }

    void                                            set_computation_module(const noise_module* computation);
    void                                            set_x_displace_module(const noise_module* displace_x);
    void                                            set_y_displace_module(const noise_module* displace_y);
    void                                            set_z_displace_module(const noise_module* displace_z);
    void                                            set_w_displace_module(const noise_module* displace_w);
protected:
    virtual void                                    on_configuration_changed() override;
};

template<unsigned int D>
inline void displace::transform(const noise_displace_module * module, vectorf<D>& point, const array<float, D>& transformation)
{
    transformer_utility::element_wise_transform(point.coords, point.coords + D, [](float v, float disp) { return v + disp; }, point.coords, transformation.begin());
}

GNOISE_NAMESPACE_END