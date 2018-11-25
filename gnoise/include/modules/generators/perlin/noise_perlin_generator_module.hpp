#pragma once

#include "../noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_perlin_frequency = 1.0f;
inline constexpr float default_perlin_lacunarity = 2.0f;
inline constexpr unsigned int default_perlin_octave_count = 6u;
inline constexpr float default_perlin_persistence = 0.5f;
inline constexpr noise_quality default_perlin_quality = noise_quality::standard;
inline constexpr int default_perlin_seed = 0;

class noise_perlin_generator_module;

struct perlin
{
    template<unsigned int D>
    inline static float generate(const noise_perlin_generator_module* module, vectorf<D> point)
    {
        float value = 0.0f;
        float signal = 0.0f;
        float current_persistence = 1.0f;
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
            value += signal * current_persistence;

            std::transform(point.coords, point.coords + D, point.coords, [&module](float v) {
                return v * module->lacunarity();
            });

            current_persistence *= module->persistence();
        }

        return value;
    }
};

class noise_perlin_generator_module : public noise_generator_module_def_impl<perlin, noise_perlin_generator_module>
{
public:
    noise_perlin_generator_module() noexcept = default;
public:
    inline float                                    frequency() const
    {
        return _frequency;
    }
    inline float                                    lacunarity() const
    {
        return _lacunarity;
    }
    inline float                                    persistence() const
    {
        return _persistence;
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

    void                                            set_frequency(float frequency);
    void                                            set_lacunarity(float lacunarity);
    void                                            set_persistence(float persistence);
    bool                                            set_octave_count(unsigned int octave_count);
    void                                            set_seed(int seed);
    void                                            set_quality(noise_quality quality);
protected:
    virtual void                                    on_configuration_changed() override;
private:
    float                                           _frequency = default_perlin_frequency;
    float                                           _lacunarity = default_perlin_lacunarity;
    float                                           _persistence = default_perlin_persistence;
    unsigned int                                    _octave_count = default_perlin_octave_count;
    int                                             _seed = default_perlin_seed;
    noise_quality                                   _quality = default_perlin_quality;
};

GNOISE_NAMESPACE_END