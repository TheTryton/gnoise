#pragma once

#include "../noise_linear_transformer_module.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_scale_point_module;

inline constexpr float default_scale_x = 1.0f;
inline constexpr float default_scale_y = 1.0f;
inline constexpr float default_scale_z = 1.0f;
inline constexpr float default_scale_w = 1.0f;

struct scale_point
{
    template<unsigned int D>
    inline static void transform(const noise_scale_point_module* module, vectorf<D>& point);
};

class noise_scale_point_module : public noise_linear_transformer_module_base_def_impl<scale_point, noise_scale_point_module>
{
public:
    noise_scale_point_module() noexcept = default;
public:
    inline const array<float, 4>&                   scale() const
    {
        return _scale;
    }
    inline float                                    scale_x() const
    {
        return _scale[0];
    }
    inline float                                    scale_y() const
    {
        return _scale[1];
    }
    inline float                                    scale_z() const
    {
        return _scale[2];
    }
    inline float                                   scale_w() const
    {
        return _scale[3];
    }

    void                                            set_scale_x(float scale_x);
    void                                            set_scale_y(float scale_y);
    void                                            set_scale_z(float scale_z);
    void                                            set_scale_w(float scale_w);
protected:
    virtual void                                    on_configuration_changed() override;
private:
    array<float, 4>                                 _scale = {
        default_scale_x,
        default_scale_y,
        default_scale_z,
        default_scale_w
    };
};

template<unsigned int D>
inline void scale_point::transform(const noise_scale_point_module* module, vectorf<D>& point)
{
    const auto& scale = module->scale();
    for (size_t i = 0; i < D; i++)
    {
        point.coords[i] *= scale[i];
    }
}

GNOISE_NAMESPACE_END