#include "noise_const_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

float noise_const_generator_module::compute(const vector1f& point) const
{
    return _const_value;
}

float noise_const_generator_module::compute(const vector2f& point) const
{
    return _const_value;
}

float noise_const_generator_module::compute(const vector3f& point) const
{
    return _const_value;
}

float noise_const_generator_module::compute(const vector4f& point) const
{
    return _const_value;
}

vector<float> noise_const_generator_module::compute(const vector<vector1f>& points) const
{
    vector<float> results(points.size(), _const_value);
    return results;
}

vector<float> noise_const_generator_module::compute(const vector<vector2f>& points) const
{
    vector<float> results(points.size(), _const_value);
    return results;
}

vector<float> noise_const_generator_module::compute(const vector<vector3f>& points) const
{
    vector<float> results(points.size(), _const_value);
    return results;
}

vector<float> noise_const_generator_module::compute(const vector<vector4f>& points) const
{
    vector<float> results(points.size(), _const_value);
    return results;
}

vector<float> noise_const_generator_module::compute(const range1f& range, const precision1& precision) const
{
    vector<float> results(
        std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()),
        _const_value
    );
    return results;
}

vector<float> noise_const_generator_module::compute(const range2f& range, const precision2& precision) const
{
    vector<float> results(
        std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()),
        _const_value
    );
    return results;
}

vector<float> noise_const_generator_module::compute(const range3f& range, const precision3& precision) const
{
    vector<float> results(
        std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()),
        _const_value
    );
    return results;
}

vector<float> noise_const_generator_module::compute(const range4f& range, const precision4& precision) const
{
    vector<float> results(
        std::accumulate(precision.begin(),precision.end(),1ull,std::multiplies<unsigned long long int>()),
        _const_value
    );
    return results;
}

float noise_const_generator_module::const_value() const
{
    return _const_value;
}

void noise_const_generator_module::set_const_value(float value)
{
    _const_value = value;
}

void noise_const_generator_module::on_configuration_changed()
{
}

GNOISE_NAMESPACE_END