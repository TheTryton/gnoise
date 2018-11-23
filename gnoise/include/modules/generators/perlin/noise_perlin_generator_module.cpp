#include "noise_perlin_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

float noise_perlin_generator_module::frequency() const
{
    return _frequency;
}

float noise_perlin_generator_module::lacunarity() const
{
    return _lacunarity;
}

float noise_perlin_generator_module::persistence() const
{
    return _persistence;
}

unsigned int noise_perlin_generator_module::octave_count() const
{
    return _octave_count;
}

int noise_perlin_generator_module::seed() const
{
    return _seed;
}

noise_quality noise_perlin_generator_module::quality() const
{
    return _quality;
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

template<unsigned int D>
float perlin_value_point(const noise_perlin_generator_module* module, vectorf<D> point)
{
    float value = 0.0f;
    float signal = 0.0f;
    float current_persistence = 1.0f;
    array<float, D> n_point;
    int seed;

    std::transform(point.coords, point.coords + D, point.coords, [&module](float v) {
        return v * module->frequency();
    });

    for(unsigned int current_octave = 0; current_octave < module->octave_count(); current_octave++)
    {
        std::transform(point.coords, point.coords + D, n_point.begin(), [&module](float v) {
            return generator_utility::make_int32_range(v);
        });

        seed = (module->seed() + current_octave) & 0xffffffff;
        signal = generator_utility::gradient_coherent_noise<D>(n_point, seed, module->quality());
        value += signal * current_persistence;

        std::transform(point.coords, point.coords + D, point.coords, [&module](float v) {
            return v * module->lacunarity();
        });

        current_persistence *= module->persistence();
    }

    return value;
}

float noise_perlin_generator_module::compute(const vector1f& point) const
{
    return perlin_value_point(this, point);
}

float noise_perlin_generator_module::compute(const vector2f& point) const
{
    return perlin_value_point(this, point);
}

float noise_perlin_generator_module::compute(const vector3f& point) const
{
    return perlin_value_point(this, point);
}

float noise_perlin_generator_module::compute(const vector4f& point) const
{
    return perlin_value_point(this, point);
}

template<unsigned int D>
vector<float> perlin_value_points_stcpu(const noise_perlin_generator_module* module, const vector<vectorf<D>>& points)
{
    vector<float> values(points.size());
    std::transform(points.begin(), points.end(), values.begin(), [&module](const vectorf<D>& v) {
        return perlin_value_point(module, v);
    });
    return values;
}

template<unsigned int D>
vector<float> perlin_value_points_mtcpu(const noise_perlin_generator_module* module, const vector<vectorf<D>>& points)
{
    vector<float> values(points.size());
    float affinity = module->configuration().multithreaded_target_configuration()->percentage_affinity();

    auto cores_assigned = static_cast<unsigned int>(std::thread::hardware_concurrency()*affinity);
    if(cores_assigned == 0)
    {
        return vector<float>();
    }

    vector<std::thread> work_threads(cores_assigned);
    auto div = static_cast<float>(points.size()) / cores_assigned;
    for(size_t i=0;i<work_threads.size();i++)
    {
        auto thread_start_it = points.begin() + static_cast<size_t>(div * i);
        auto thread_end_it = points.begin() + static_cast<size_t>(div * (i + 1));
        auto thread_start_values_it = values.begin() + static_cast<size_t>(div * i);
        work_threads[i] = std::thread([thread_start_it, thread_end_it, thread_start_values_it, &values, &points, &module]() {
            std::transform(thread_start_it, thread_end_it, thread_start_values_it, [&module](const vectorf<D>& v) {
                return perlin_value_point(module, v);
            });
        });
    }

    for (auto& thread : work_threads)
    {
        thread.join();
    }
    
    return values;
}

vector<float> noise_perlin_generator_module::compute(const vector<vector1f>& points) const
{
    if(points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return perlin_value_points_stcpu(this, points);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return perlin_value_points_mtcpu(this, points);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_perlin_generator_module::compute(const vector<vector2f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return perlin_value_points_stcpu(this, points);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return perlin_value_points_mtcpu(this, points);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_perlin_generator_module::compute(const vector<vector3f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return perlin_value_points_stcpu(this, points);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return perlin_value_points_mtcpu(this, points);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_perlin_generator_module::compute(const vector<vector4f>& points) const
{
    if (points.size() == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return perlin_value_points_stcpu(this, points);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return perlin_value_points_mtcpu(this, points);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

template<unsigned int D>
vector<float> perlin_value_range_stcpu(const noise_perlin_generator_module* module, const rangef<D>& range, const precision<D>& precision)
{
    unsigned long long int precision_all_dim = std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>());
    vector<float> values(precision_all_dim);
    for (unsigned long long int i = 0; i < precision_all_dim; i++)
    {
        array<unsigned long long int, D> coord_prec;
        
        unsigned long long int curr_div = 1;
        
        for (size_t j = 0; j < D; j++)
        {
            coord_prec[j] = (i / curr_div) % precision[j];
            curr_div *= precision[j];
        }

        vectorf<D> coords;
        
        for (size_t j = 0; j < D; j++)
        {
            coords.coords[j] = coord_prec[j] / static_cast<float>(precision[j]);
        }

        for (size_t j = 0; j < D; j++)
        {
            coords.coords[j] = generator_utility::interpolate_linear(range[j].coords[0], range[j].coords[1], coords.coords[j]);
        }

        values[i] = perlin_value_point(module, coords);
    }
    
    return values;
}

template<unsigned int D>
vector<float> perlin_value_range_mtcpu(const noise_perlin_generator_module* module, const rangef<D>& range, const precision<D>& precision)
{
    unsigned long long int precision_all_dim = std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>());
    vector<float> values(precision_all_dim);

    float affinity = module->configuration().multithreaded_target_configuration()->percentage_affinity();

    auto cores_assigned = static_cast<unsigned int>(std::thread::hardware_concurrency()*affinity);
    if (cores_assigned == 0)
    {
        return vector<float>();
    }

    vector<std::thread> work_threads(cores_assigned);
    auto div = static_cast<double>(precision_all_dim) / cores_assigned;
    for (size_t i = 0; i < work_threads.size(); i++)
    {
        auto thread_start_it = static_cast<size_t>(div * i);
        auto thread_end_it = static_cast<size_t>(div * (i + 1));

        work_threads[i] = std::thread([thread_start_it, thread_end_it, &values, &range, &precision, &module]() {
            for (unsigned long long int i = thread_start_it; i < thread_end_it; i++)
            {
                array<unsigned long long int, D> coord_prec;

                unsigned long long int curr_div = 1;

                for (size_t j = 0; j < D; j++)
                {
                    coord_prec[j] = (i / curr_div) % precision[j];
                    curr_div *= precision[j];
                }

                vectorf<D> coords;

                for (size_t j = 0; j < D; j++)
                {
                    coords.coords[j] = coord_prec[j] / static_cast<float>(precision[j]);
                }

                for (size_t j = 0; j < D; j++)
                {
                    coords.coords[j] = generator_utility::interpolate_linear(range[j].coords[0], range[j].coords[1], coords.coords[j]);
                }

                values[i] = perlin_value_point(module, coords);
            }
        });
    }

    for (auto& thread : work_threads)
    {
        thread.join();
    }

    return values;
}

vector<float> noise_perlin_generator_module::compute(const range1f& range, const precision1& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return perlin_value_range_stcpu(this, range, precision);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return perlin_value_range_mtcpu(this, range, precision);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_perlin_generator_module::compute(const range2f& range, const precision2& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return perlin_value_range_stcpu(this, range, precision);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return perlin_value_range_mtcpu(this, range, precision);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_perlin_generator_module::compute(const range3f& range, const precision3& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return perlin_value_range_stcpu(this, range, precision);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return perlin_value_range_mtcpu(this, range, precision);
    }
    break;
    case module_computation_target::open_cl:
    {

    }
    break;
    }

    return vector<float>();
}

vector<float> noise_perlin_generator_module::compute(const range4f& range, const precision4& precision) const
{
    if (std::accumulate(precision.begin(), precision.end(), 1ull, std::multiplies<unsigned long long int>()) == 0)
    {
        return vector<float>();
    }

    switch (_configuration.computation_target())
    {
    case module_computation_target::single_thread_cpu:
    {
        return perlin_value_range_stcpu(this, range, precision);
    }
    break;
    case module_computation_target::multi_thread_cpu:
    {
        return perlin_value_range_mtcpu(this, range, precision);
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