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

    static void create_kernels(
        cl_device_id target_device, const cl_context& context,
        array<cl_program, 4>& program_points,
        array<cl_kernel, 4>& kernel_points,
        array<cl_program, 4>& program_ranges,
        array<cl_kernel, 4>& kernel_ranges
    );

    static array<float, 0> get_module_config_f(const noise_checkerboard_generator_module* module);
    static array<int, 0> get_module_config_i(const noise_checkerboard_generator_module* module);
};

class noise_checkerboard_generator_module : public noise_generator_module_def_impl<checkerboard, noise_checkerboard_generator_module>
{
public:
    noise_checkerboard_generator_module() noexcept = default;
};

GNOISE_NAMESPACE_END