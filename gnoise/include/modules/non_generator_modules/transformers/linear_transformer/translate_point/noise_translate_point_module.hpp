#pragma once

#include "../noise_linear_transformer_module.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_translate_point_module;

inline constexpr float default_translation_x = 0.0f;
inline constexpr float default_translation_y = 0.0f;
inline constexpr float default_translation_z = 0.0f;
inline constexpr float default_translation_w = 0.0f;

struct translate_point
{
    template<unsigned int D>
    inline static void transform(const noise_translate_point_module* module, vectorf<D>& point);
};

class noise_translate_point_module : public noise_linear_transformer_module_base_def_impl<translate_point, noise_translate_point_module>
{
public:
    noise_translate_point_module() noexcept = default;
public:
    inline const array<float, 4>&                   translation() const
    {
        return _translation;
    }
    inline float                                    translation_x() const
    {
        return _translation[0];
    }
    inline float                                    translation_y() const
    {
        return _translation[1];
    }
    inline float                                    translation_z() const
    {
        return _translation[2];
    }
    inline float                                    translation_w() const
    {
        return _translation[3];
    }

    void                                            set_translation_x(float translation_x);
    void                                            set_translation_y(float translation_y);
    void                                            set_translation_z(float translation_z);
    void                                            set_translation_w(float translation_w);
protected:
    virtual void                                    on_configuration_changed() override;
private:
    array<float, 4>                                 _translation = {
        default_translation_x,
        default_translation_y,
        default_translation_z,
        default_translation_w 
    };
};

template<unsigned int D>
inline void translate_point::transform(const noise_translate_point_module* module, vectorf<D>& point)
{
    const auto& translation = module->translation();
    for (size_t i = 0; i < D; i++)
    {
        point.coords[i] += translation[i];
    }
}

GNOISE_NAMESPACE_END