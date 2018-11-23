#include "noise_checkerboard_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

void noise_checkerboard_generator_module::on_configuration_changed()
{
    //TODO
}

template<unsigned int D>
inline float checkerboard_value_point(const noise_checkerboard_generator_module* module, vectorf<D> point)
{
    array<int, D> point_i;

    std::transform(point.coords, point.coords + D, point_i.begin(), [&module](float v) {
        return static_cast<int>(floorf(generator_utility::make_int32_range(v))) & 1;
    });

    return static_cast<bool>(std::accumulate(point_i.begin(), point_i.end(), 0, [](int a, int b) {
        return a ^ b;
    })) ? -1.0f : 1.0f;
}

float noise_checkerboard_generator_module::compute(const vector1f& point) const
{
    return checkerboard_value_point(this, point);
}

float noise_checkerboard_generator_module::compute(const vector2f& point) const
{
    return checkerboard_value_point(this, point);
}

float noise_checkerboard_generator_module::compute(const vector3f& point) const
{
    return checkerboard_value_point(this, point);
}

float noise_checkerboard_generator_module::compute(const vector4f& point) const
{
    return checkerboard_value_point(this, point);
}

vector<float> noise_checkerboard_generator_module::compute(const vector<vector1f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, checkerboard_value_point<1>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, checkerboard_value_point<1>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_checkerboard_generator_module::compute(const vector<vector2f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, checkerboard_value_point<2>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, checkerboard_value_point<2>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_checkerboard_generator_module::compute(const vector<vector3f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, checkerboard_value_point<3>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, checkerboard_value_point<3>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_checkerboard_generator_module::compute(const vector<vector4f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, checkerboard_value_point<4>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, checkerboard_value_point<4>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_checkerboard_generator_module::compute(const range1f& range, const precision1& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, checkerboard_value_point<1>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, checkerboard_value_point<1>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_checkerboard_generator_module::compute(const range2f& range, const precision2& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, checkerboard_value_point<2>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, checkerboard_value_point<2>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_checkerboard_generator_module::compute(const range3f& range, const precision3& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, checkerboard_value_point<3>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, checkerboard_value_point<3>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_checkerboard_generator_module::compute(const range4f& range, const precision4& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, checkerboard_value_point<4>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, checkerboard_value_point<4>);
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