#pragma once

#include "../noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_cylinders_frequency = 1.0f;

class noise_cylinders_generator_module;

struct cylinders
{
    template<unsigned int D>
    inline static float generate(const noise_cylinders_generator_module* module, vectorf<D> point)
    {
        if constexpr (D <= 2)
        {
            std::transform(point.coords, point.coords + 1, point.coords, [&module](float v) {
                return v * module->frequency();
            });

            auto dist_from_center = std::inner_product(point.coords, point.coords + 1, point.coords, 0.0f);
            auto dist_from_smaller_sphere = dist_from_center - floorf(dist_from_center);
            auto dist_from_larger_sphere = 1.0f - dist_from_smaller_sphere;
            auto nearest_dist = std::min(dist_from_smaller_sphere, dist_from_larger_sphere);
            return 1.0f - (nearest_dist * 4.0f);
        }
        if constexpr (D > 2)
        {
            std::transform(point.coords, point.coords + 1, point.coords, [&module](float v) {
                return v * module->frequency();
            });

            std::transform(point.coords + 2, point.coords + D, point.coords + 2, [&module](float v) {
                return v * module->frequency();
            });

            auto dist_from_center = sqrtf(
                std::inner_product(point.coords, point.coords + 1, point.coords, 0.0f) +
                std::inner_product(point.coords + 2, point.coords + D, point.coords + 2, 0.0f)
            );
            auto dist_from_smaller_sphere = dist_from_center - floorf(dist_from_center);
            auto dist_from_larger_sphere = 1.0f - dist_from_smaller_sphere;
            auto nearest_dist = std::min(dist_from_smaller_sphere, dist_from_larger_sphere);
            return 1.0f - (nearest_dist * 4.0f);
        }
    }
};

class noise_cylinders_generator_module : public noise_generator_module_def_impl<cylinders, noise_cylinders_generator_module>
{
public:
    noise_cylinders_generator_module() noexcept = default;
public:
    inline float                                    frequency() const
    {
        return _frequency;
    }

    void                                            set_frequency(float frequency);
protected:
    virtual void                                    on_configuration_changed() override;
private:
    float                                           _frequency = default_cylinders_frequency;
};

GNOISE_NAMESPACE_END