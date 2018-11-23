#include "noise_ridged_multifractal_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline float noise_ridged_multifractal_generator_module::frequency() const
{
    return _frequency;
}

inline float noise_ridged_multifractal_generator_module::lacunarity() const
{
    return _lacunarity;
}

inline unsigned int noise_ridged_multifractal_generator_module::octave_count() const
{
    return _octave_count;
}

inline int noise_ridged_multifractal_generator_module::seed() const
{
    return _seed;
}

inline noise_quality noise_ridged_multifractal_generator_module::quality() const
{
    return _quality;
}

inline const vector<float>& noise_ridged_multifractal_generator_module::weights() const
{
    return _weights;
}

void noise_ridged_multifractal_generator_module::set_frequency(float frequency)
{
    _frequency = frequency;
}

void noise_ridged_multifractal_generator_module::set_lacunarity(float lacunarity)
{
    _lacunarity = lacunarity;
    calculate_weights();
}

bool noise_ridged_multifractal_generator_module::set_octave_count(unsigned int octave_count)
{
    if (octave_count > maximum_octave_count)
    {
        return false;
    }
    _octave_count = octave_count;
    return true;
}

void noise_ridged_multifractal_generator_module::set_seed(int seed)
{
    _seed = seed;
}

void noise_ridged_multifractal_generator_module::set_quality(noise_quality quality)
{
    _quality = quality;
}

void noise_ridged_multifractal_generator_module::calculate_weights()
{
    float h = 1.0f;
    float freq = 1.0f;
    for (unsigned int i = 0; i < maximum_octave_count; i++)
    {
        _weights[i] = std::pow(freq, -h);
        freq *= _lacunarity;
    }
}

void noise_ridged_multifractal_generator_module::on_configuration_changed()
{
    //TODO
}

template<unsigned int D>
inline float ridged_multifractal_value_point(const noise_ridged_multifractal_generator_module* module, vectorf<D> point)
{
    float value = 0.0f;
    float signal = 0.0f;
    float weight = 1.0f;
    float offset = 1.0f;
    float gain = 2.0f;

    array<float, D> n_point;

    int seed;

    std::transform(point.coords, point.coords + D, point.coords, [&module](float v) {
        return v * module->frequency();
    });

    for (unsigned int current_octave = 0; current_octave < module->octave_count(); current_octave++)
    {
        std::transform(point.coords, point.coords + D, n_point.begin(), [&module](float v) {
            return generator_utility::make_int32_range(v);
        });

        seed = (module->seed() + current_octave) & 0xffffffff;
        signal = generator_utility::gradient_coherent_noise<D>(n_point, seed, module->quality());
        signal = fabs(signal);
        signal = offset - signal;
        signal *= signal;
        signal *= weight;
        weight = signal * gain;
        weight = generator_utility::clamp(weight, 0.0f, 1.0f);

        value += signal * module->weights()[current_octave];

        std::transform(point.coords, point.coords + D, point.coords, [&module](float v) {
            return v * module->lacunarity();
        });
    }

    return value * 1.25f - 1.0f;
}

noise_ridged_multifractal_generator_module::noise_ridged_multifractal_generator_module() noexcept :
    noise_generator_module()
{
    calculate_weights();
}

float noise_ridged_multifractal_generator_module::compute(const vector1f& point) const
{
    return ridged_multifractal_value_point(this, point);
}

float noise_ridged_multifractal_generator_module::compute(const vector2f& point) const
{
    return ridged_multifractal_value_point(this, point);
}

float noise_ridged_multifractal_generator_module::compute(const vector3f& point) const
{
    return ridged_multifractal_value_point(this, point);
}

float noise_ridged_multifractal_generator_module::compute(const vector4f& point) const
{
    return ridged_multifractal_value_point(this, point);
}

vector<float> noise_ridged_multifractal_generator_module::compute(const vector<vector1f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, ridged_multifractal_value_point<1>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, ridged_multifractal_value_point<1>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_ridged_multifractal_generator_module::compute(const vector<vector2f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, ridged_multifractal_value_point<2>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, ridged_multifractal_value_point<2>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_ridged_multifractal_generator_module::compute(const vector<vector3f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, ridged_multifractal_value_point<3>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, ridged_multifractal_value_point<3>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_ridged_multifractal_generator_module::compute(const vector<vector4f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_points_stcpu(this, points, ridged_multifractal_value_point<4>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_points_mtcpu(this, points, ridged_multifractal_value_point<4>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_ridged_multifractal_generator_module::compute(const range1f& range, const precision1& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, ridged_multifractal_value_point<1>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, ridged_multifractal_value_point<1>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_ridged_multifractal_generator_module::compute(const range2f& range, const precision2& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, ridged_multifractal_value_point<2>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, ridged_multifractal_value_point<2>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_ridged_multifractal_generator_module::compute(const range3f& range, const precision3& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, ridged_multifractal_value_point<3>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, ridged_multifractal_value_point<3>);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_ridged_multifractal_generator_module::compute(const range4f& range, const precision4& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return generator_utility::value_range_stcpu(this, range, precision, ridged_multifractal_value_point<4>);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return generator_utility::value_range_mtcpu(this, range, precision, ridged_multifractal_value_point<4>);
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