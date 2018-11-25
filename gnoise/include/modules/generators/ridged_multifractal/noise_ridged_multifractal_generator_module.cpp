#include "noise_ridged_multifractal_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

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
    noise_generator_module_def_impl()
{
    calculate_weights();
}

GNOISE_NAMESPACE_END