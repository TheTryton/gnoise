#include "noise_spheres_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

float noise_spheres_generator_module::frequency() const
{
    return _frequency;
}

void noise_spheres_generator_module::set_frequency(float frequency)
{
    _frequency = frequency;
}

void noise_spheres_generator_module::on_configuration_changed()
{
    //TODO
}

template<unsigned int D>
inline float spheres_value_point(const noise_spheres_generator_module* module, vectorf<D> point)
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

float noise_spheres_generator_module::compute(const vector1f& point) const
{
    return spheres_value_point(this, point);
}

float noise_spheres_generator_module::compute(const vector2f& point) const
{
    return spheres_value_point(this, point);
}

float noise_spheres_generator_module::compute(const vector3f& point) const
{
    return spheres_value_point(this, point);
}

float noise_spheres_generator_module::compute(const vector4f& point) const
{
    return spheres_value_point(this, point);
}

vector<float> noise_spheres_generator_module::compute(const vector<vector1f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, spheres_value_point<1>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, spheres_value_point<1>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_spheres_generator_module::compute(const vector<vector2f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, spheres_value_point<2>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, spheres_value_point<2>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_spheres_generator_module::compute(const vector<vector3f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, spheres_value_point<3>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, spheres_value_point<3>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_spheres_generator_module::compute(const vector<vector4f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, spheres_value_point<4>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, spheres_value_point<4>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_spheres_generator_module::compute(const range1f& range, const precision1& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, spheres_value_point<1>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, spheres_value_point<1>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_spheres_generator_module::compute(const range2f& range, const precision2& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, spheres_value_point<2>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, spheres_value_point<2>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_spheres_generator_module::compute(const range3f& range, const precision3& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, spheres_value_point<3>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, spheres_value_point<3>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_spheres_generator_module::compute(const range4f& range, const precision4& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, spheres_value_point<4>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, spheres_value_point<4>);
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