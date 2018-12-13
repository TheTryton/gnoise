#include "noise_perlin_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline array<float, 3> perlin::get_module_config_f(const noise_perlin_generator_module* module)
{
    return { module->frequency(), module->lacunarity(), module->persistence() };
}

inline array<int, 3> perlin::get_module_config_i(const noise_perlin_generator_module* module)
{
    return { static_cast<int>(module->octave_count()), module->seed(), static_cast<int>(module->quality())};
}

void noise_perlin_generator_module::set_frequency(float frequency)
{
    _frequency = frequency;
}

void noise_perlin_generator_module::set_lacunarity(float lacunarity)
{
    _lacunarity = lacunarity;
}

void noise_perlin_generator_module::set_persistence(float persistence)
{
    _persistence = persistence;
}

bool noise_perlin_generator_module::set_octave_count(unsigned int octave_count)
{
    if(octave_count > maximum_octave_count)
    {
        return false;
    }
    _octave_count = octave_count;
    return true;
}

void noise_perlin_generator_module::set_seed(int seed)
{
    _seed = seed;
}

void noise_perlin_generator_module::set_quality(noise_quality quality)
{
    _quality = quality;
}

void noise_perlin_generator_module::on_configuration_changed()
{
    //TODO
}

GNOISE_NAMESPACE_END