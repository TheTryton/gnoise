#include "noise_voronoi_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

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

GNOISE_NAMESPACE_END