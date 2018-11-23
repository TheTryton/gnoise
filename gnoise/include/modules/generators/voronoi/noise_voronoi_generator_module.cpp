#include "noise_voronoi_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline float noise_voronoi_generator_module::frequency() const
{
    return _frequency;
}

inline float noise_voronoi_generator_module::displacement() const
{
    return _displacement;
}

inline int noise_voronoi_generator_module::seed() const
{
    return _seed;
}

inline bool noise_voronoi_generator_module::uses_distance() const
{
    return _use_distance;
}

void noise_voronoi_generator_module::set_frequency(float frequency)
{
    _frequency = frequency;
}

void noise_voronoi_generator_module::set_displacement(float displacement)
{
    _displacement = displacement;
}

void noise_voronoi_generator_module::set_seed(int seed)
{
    _seed = seed;
}

void noise_voronoi_generator_module::set_use_distance(bool use_distance)
{
    _use_distance = use_distance;
}

void noise_voronoi_generator_module::on_configuration_changed()
{
    //TODO
}

template<unsigned int D>
inline float voronoi_value_point(const noise_voronoi_generator_module* module, vectorf<D> point)
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

    if constexpr(D == 1)
    {
        array<int, D> dim_current;

        for (dim_current[0] = int_point[0] - 2; dim_current[0] <= int_point[0] + 2; dim_current[0]++)
        {
            array<float, D> point_pos;
            for(size_t i=0;i<D;i++)
            {
                point_pos[i] = dim_current[0] + generator_utility::value_noise(dim_current, module->seed() + i);
            }
            array<float, D> point_dist;
            for(size_t i=0;i<D;i++)
            {
                point_dist[i] = point_pos[i] - point.coords[i];
            }
            auto dist = std::inner_product(point_dist.begin(), point_dist.end(), point_dist.begin(), 0.0f);
            if(dist < min_distance)
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
                    point_pos[i] = dim_current[i] + generator_utility::value_noise(dim_current, module->seed() + i);
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
                        point_pos[i] = dim_current[i] + generator_utility::value_noise(dim_current, module->seed() + i);
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
                            point_pos[i] = dim_current[i] + generator_utility::value_noise(dim_current, module->seed() + i);
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

float noise_voronoi_generator_module::compute(const vector1f& point) const
{
    return voronoi_value_point(this, point);
}

float noise_voronoi_generator_module::compute(const vector2f& point) const
{
    return voronoi_value_point(this, point);
}

float noise_voronoi_generator_module::compute(const vector3f& point) const
{
    return voronoi_value_point(this, point);
}

float noise_voronoi_generator_module::compute(const vector4f& point) const
{
    return voronoi_value_point(this, point);
}

vector<float> noise_voronoi_generator_module::compute(const vector<vector1f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, voronoi_value_point<1>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, voronoi_value_point<1>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_voronoi_generator_module::compute(const vector<vector2f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, voronoi_value_point<2>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, voronoi_value_point<2>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_voronoi_generator_module::compute(const vector<vector3f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, voronoi_value_point<3>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, voronoi_value_point<3>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_voronoi_generator_module::compute(const vector<vector4f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, voronoi_value_point<4>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, voronoi_value_point<4>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_voronoi_generator_module::compute(const range1f& range, const precision1& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, voronoi_value_point<1>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, voronoi_value_point<1>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_voronoi_generator_module::compute(const range2f& range, const precision2& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, voronoi_value_point<2>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, voronoi_value_point<2>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_voronoi_generator_module::compute(const range3f& range, const precision3& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, voronoi_value_point<3>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, voronoi_value_point<3>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_voronoi_generator_module::compute(const range4f& range, const precision4& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, voronoi_value_point<4>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, voronoi_value_point<4>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

GNOISE_NAMESPACE_END