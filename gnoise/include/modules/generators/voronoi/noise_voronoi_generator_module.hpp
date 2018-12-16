#pragma once

#include "../noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_voronoi_frequency = 1.0f;
inline constexpr float default_voronoi_displacement = 2.0f;
inline constexpr int default_voronoi_seed = 0;
inline constexpr bool default_voronoi_use_distance = 0;

class noise_voronoi_generator_module;

struct voronoi
{
    template<unsigned int D>
    inline static float generate(const noise_voronoi_generator_module* module, vectorf<D> point)
    {
        static_assert(D != 0, "noise dimension must be greater than 0");
        static_assert(D <= 4, "dimension higher than 4 has no noise implentation");

        std::transform(point.coords, point.coords + D, point.coords, [&module](float v) {
            return v * module->frequency();
        });

        array<int, D> int_point;
        std::transform(point.coords, point.coords + D, int_point.begin(), [](float v) {
            return v > 0.0f ? static_cast<int>(v) : static_cast<int>(v) - 1;
        });

        float min_distance = static_cast<float>(std::numeric_limits<int>::max());
        array<float, D> point_candidate;

        if constexpr (D == 1)
        {
            array<int, D> dim_current;

            for (dim_current[0] = int_point[0] - 2; dim_current[0] <= int_point[0] + 2; dim_current[0]++)
            {
                array<float, D> point_pos;
                for (size_t i = 0; i < D; i++)
                {
                    point_pos[i] = dim_current[0] + generator_utility::value_noise(dim_current, module->seed() + static_cast<int>(i));
                }
                array<float, D> point_dist;
                for (size_t i = 0; i < D; i++)
                {
                    point_dist[i] = point_pos[i] - point.coords[i];
                }
                auto dist = std::inner_product(point_dist.begin(), point_dist.end(), point_dist.begin(), 0.0f);
                if (dist < min_distance)
                {
                    min_distance = dist;
                    std::copy(point_pos.begin(), point_pos.end(), point_candidate.begin());
                }
            }
        }
        if constexpr (D == 2)
        {
            array<int, D> dim_current;


            for (dim_current[0] = int_point[0] - 2; dim_current[0] <= int_point[0] + 2; dim_current[0]++)
            {
                for (dim_current[1] = int_point[1] - 2; dim_current[1] <= int_point[1] + 2; dim_current[1]++)
                {
                    array<float, D> point_pos;
                    for (size_t i = 0; i < D; i++)
                    {
                        point_pos[i] = dim_current[i] + generator_utility::value_noise(dim_current, module->seed() + static_cast<int>(i));
                    }
                    array<float, D> point_dist;
                    for (size_t i = 0; i < D; i++)
                    {
                        point_dist[i] = point_pos[i] - point.coords[i];
                    }
                    auto dist = std::inner_product(point_dist.begin(), point_dist.end(), point_dist.begin(), 0.0f);
                    if (dist < min_distance)
                    {
                        min_distance = dist;
                        std::copy(point_pos.begin(), point_pos.end(), point_candidate.begin());
                    }
                }
            }
        }
        if constexpr (D == 3)
        {
            array<int, D> dim_current;

            for (dim_current[0] = int_point[0] - 2; dim_current[0] <= int_point[0] + 2; dim_current[0]++)
            {
                for (dim_current[1] = int_point[1] - 2; dim_current[1] <= int_point[1] + 2; dim_current[1]++)
                {
                    for (dim_current[2] = int_point[2] - 2; dim_current[2] <= int_point[1] + 2; dim_current[2]++)
                    {
                        array<float, D> point_pos;
                        for (size_t i = 0; i < D; i++)
                        {
                            point_pos[i] = dim_current[i] + generator_utility::value_noise(dim_current, module->seed() + static_cast<int>(i));
                        }
                        array<float, D> point_dist;
                        for (size_t i = 0; i < D; i++)
                        {
                            point_dist[i] = point_pos[i] - point.coords[i];
                        }
                        auto dist = std::inner_product(point_dist.begin(), point_dist.end(), point_dist.begin(), 0.0f);
                        if (dist < min_distance)
                        {
                            min_distance = dist;
                            std::copy(point_pos.begin(), point_pos.end(), point_candidate.begin());
                        }
                    }
                }
            }
        }
        if constexpr (D == 4)
        {
            array<int, D> dim_current;

            std::transform(int_point.begin(), int_point.end(), dim_current.begin(), [](int v) {
                return v - 2;
            });

            for (; dim_current[0] <= int_point[0] + 2; dim_current[0]++)
            {
                for (; dim_current[1] <= int_point[1] + 2; dim_current[1]++)
                {
                    for (; dim_current[2] <= int_point[2] + 2; dim_current[2]++)
                    {
                        for (; dim_current[3] <= int_point[3] + 2; dim_current[3]++)
                        {
                            array<float, D> point_pos;
                            for (size_t i = 0; i < D; i++)
                            {
                                point_pos[i] = dim_current[i] + generator_utility::value_noise(dim_current, module->seed() + static_cast<int>(i));
                            }
                            array<float, D> point_dist;
                            for (size_t i = 0; i < D; i++)
                            {
                                point_dist[i] = point_pos[i] - point.coords[i];
                            }
                            auto dist = std::inner_product(point_dist.begin(), point_dist.end(), point_dist.begin(), 0.0f);
                            if (dist < min_distance)
                            {
                                min_distance = dist;
                                std::copy(point_pos.begin(), point_pos.end(), point_candidate.begin());
                            }
                        }
                    }
                }
            }
        }

        float value = 0.0f;
        if (module->uses_distance())
        {
            array<float, D> point_dist;
            for (size_t i = 0; i < D; i++)
            {
                point_dist[i] = point_candidate[i] - point.coords[i];
            }
            value = sqrtf(std::inner_product(point_dist.begin(), point_dist.end(), point_dist.begin(), 0.0f))*generator_utility::sqrt_3 - 1.0f;
        }
        else
        {
            value = 0.0f;
        }

        array<int, D> point_candidate_i;
        std::transform(point_candidate.begin(), point_candidate.end(), point_candidate_i.begin(), [](float v) {
            return static_cast<int>(floorf(v));
        });

        return value + module->displacement() * generator_utility::value_noise(point_candidate_i, 0);
    }

    static void create_kernels(
        cl_device_id target_device, const cl_context& context,
        array<cl_program, 4>& program_points,
        array<cl_kernel, 4>& kernel_points,
        array<cl_program, 4>& program_ranges,
        array<cl_kernel, 4>& kernel_ranges
    );

    static array<float, 2> get_module_config_f(const noise_voronoi_generator_module* module);
    static array<int, 2> get_module_config_i(const noise_voronoi_generator_module* module);
};

class noise_voronoi_generator_module : public noise_generator_module_def_impl<voronoi, noise_voronoi_generator_module>
{
public:
    noise_voronoi_generator_module() noexcept = default;
public:
    inline float                                    frequency() const
    {
        return _frequency;
    }
    inline float                                    displacement() const
    {
        return _displacement;
    }
    inline int                                      seed() const
    {
        return _seed;
    }
    inline bool                                     uses_distance() const
    {
        return _use_distance;
    }

    void                                            set_frequency(float frequency);
    void                                            set_displacement(float displacement);
    void                                            set_seed(int seed);
    void                                            set_use_distance(bool use_distance);
private:
    float                                           _frequency = default_voronoi_frequency;
    float                                           _displacement = default_voronoi_displacement;
    int                                             _seed = default_voronoi_seed;
    bool                                            _use_distance = default_voronoi_use_distance;
};

GNOISE_NAMESPACE_END