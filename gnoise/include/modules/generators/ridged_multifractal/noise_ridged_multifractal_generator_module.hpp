#pragma once

#include "../noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_ridged_multifractal_frequency = 1.0f;
inline constexpr float default_ridged_multifractal_lacunarity = 2.0f;
inline constexpr unsigned int default_ridged_multifractal_octave_count = 6u;
inline constexpr noise_quality default_ridged_multifractal_quality = noise_quality::standard;
inline constexpr int default_ridged_multifractal_seed = 0;

class noise_ridged_multifractal_generator_module;

struct ridged_multifractal
{
    template<unsigned int D>
    inline static float generate(const noise_ridged_multifractal_generator_module* module, vectorf<D> point)
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

    static void create_kernels(
        cl_device_id target_device, const cl_context& context,
        array<cl_program, 4>& program_points,
        array<cl_kernel, 4>& kernel_points,
        array<cl_program, 4>& program_ranges,
        array<cl_kernel, 4>& kernel_ranges
    );

    static array<float, maximum_octave_count + 2> get_module_config_f(const noise_ridged_multifractal_generator_module* module);
    static array<int, 3> get_module_config_i(const noise_ridged_multifractal_generator_module* module);
};

class noise_ridged_multifractal_generator_module : public noise_generator_module_def_impl<ridged_multifractal, noise_ridged_multifractal_generator_module>
{
public:
    noise_ridged_multifractal_generator_module() noexcept;
public:
    inline float                                    frequency() const
    {
        return _frequency;
    }
    inline float                                    lacunarity() const
    {
        return _lacunarity;
    }
    inline unsigned int                             octave_count() const
    {
        return _octave_count;
    }
    inline int                                      seed() const
    {
        return _seed;
    }
    inline noise_quality                            quality() const
    {
        return _quality;
    }
    inline const vector<float>&                     weights() const
    {
        return _weights;
    }

    void                                            set_frequency(float frequency);
    void                                            set_lacunarity(float lacunarity);
    bool                                            set_octave_count(unsigned int octave_count);
    void                                            set_seed(int seed);
    void                                            set_quality(noise_quality quality);
private:
    void                                            calculate_weights();
private:
    float                                           _frequency = default_ridged_multifractal_frequency;
    float                                           _lacunarity = default_ridged_multifractal_lacunarity;
    unsigned int                                    _octave_count = default_ridged_multifractal_octave_count;
    int                                             _seed = default_ridged_multifractal_seed;
    noise_quality                                   _quality = default_ridged_multifractal_quality;
    vector<float>                                   _weights = vector<float>(maximum_octave_count);
};

GNOISE_NAMESPACE_END