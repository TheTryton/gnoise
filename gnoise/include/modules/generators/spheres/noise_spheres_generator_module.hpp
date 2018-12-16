#pragma once

#include "../noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_spheres_frequency = 1.0f;

class noise_spheres_generator_module;

struct spheres
{
    template<unsigned int D>
    inline static float generate(const noise_spheres_generator_module* module, vectorf<D> point)
    {
        std::transform(point.coords, point.coords + D, point.coords, [&module](float v) {
            return v * module->frequency();
        });

        auto dist_from_center = sqrtf(std::inner_product(point.coords, point.coords + D, point.coords, 0.0f));
        auto dist_from_smaller_sphere = dist_from_center - floorf(dist_from_center);
        auto dist_from_larger_sphere = 1.0f - dist_from_smaller_sphere;
        auto nearest_dist = std::min(dist_from_smaller_sphere, dist_from_larger_sphere);
        return 1.0f - (nearest_dist * 4.0f);
    }

    static void create_kernels(
        cl_device_id target_device, const cl_context& context,
        array<cl_program, 4>& program_points,
        array<cl_kernel, 4>& kernel_points,
        array<cl_program, 4>& program_ranges,
        array<cl_kernel, 4>& kernel_ranges
    );

    static array<float, 1> get_module_config_f(const noise_spheres_generator_module* module);
    static array<int, 0> get_module_config_i(const noise_spheres_generator_module* module);
};

class noise_spheres_generator_module : public noise_generator_module_def_impl<spheres, noise_spheres_generator_module>
{
public:
    noise_spheres_generator_module() noexcept = default;
public:
    inline float frequency() const
    {
        return _frequency;
    }

    void                                            set_frequency(float frequency);
private:
    float                                           _frequency = default_spheres_frequency;
};

GNOISE_NAMESPACE_END