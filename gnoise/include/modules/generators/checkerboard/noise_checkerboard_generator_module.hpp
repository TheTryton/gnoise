#pragma once

#include "../noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_checkerboard_generator_module;

struct checkerboard
{
    template<unsigned int D>
    inline static float generate(const noise_checkerboard_generator_module* module, vectorf<D> point)
    {
        array<int, D> point_i;

        std::transform(point.coords, point.coords + D, point_i.begin(), [&module](float v) {
            return static_cast<int>(floorf(generator_utility::make_int32_range(v))) & 1;
        });

        return static_cast<bool>(std::accumulate(point_i.begin(), point_i.end(), 0, [](int a, int b) {
            return a ^ b;
        })) ? -1.0f : 1.0f;
    }
};

class noise_checkerboard_generator_module : public noise_generator_module_def_impl<checkerboard, noise_checkerboard_generator_module>
{
public:
    noise_checkerboard_generator_module() noexcept = default;
protected:
    virtual void                                    on_configuration_changed() override;
};

GNOISE_NAMESPACE_END