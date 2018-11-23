#pragma once

#include "../noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_ridged_multifractal_frequency = 1.0f;
inline constexpr float default_ridged_multifractal_lacunarity = 2.0f;
inline constexpr unsigned int default_ridged_multifractal_octave_count = 6u;
inline constexpr noise_quality default_ridged_multifractal_quality = noise_quality::standard;
inline constexpr int default_ridged_multifractal_seed = 0;

class noise_ridged_multifractal_generator_module : public noise_generator_module
{
public:
    noise_ridged_multifractal_generator_module() noexcept;
public:
    virtual float                                   compute(const vector1f& point) const override;
    virtual float                                   compute(const vector2f& point) const override;
    virtual float                                   compute(const vector3f& point) const override;
    virtual float                                   compute(const vector4f& point) const override;

    virtual vector<float>                           compute(const vector<vector1f>& points) const override;
    virtual vector<float>                           compute(const vector<vector2f>& points) const override;
    virtual vector<float>                           compute(const vector<vector3f>& points) const override;
    virtual vector<float>                           compute(const vector<vector4f>& points) const override;

    virtual vector<float>                           compute(const range1f& range, const precision1& precision) const override;
    virtual vector<float>                           compute(const range2f& range, const precision2& precision) const override;
    virtual vector<float>                           compute(const range3f& range, const precision3& precision) const override;
    virtual vector<float>                           compute(const range4f& range, const precision4& precision) const override;

    inline float                                    frequency() const;
    inline float                                    lacunarity() const;
    inline unsigned int                             octave_count() const;
    inline int                                      seed() const;
    inline noise_quality                            quality() const;
    inline const vector<float>&                     weights() const;

    void                                            set_frequency(float frequency);
    void                                            set_lacunarity(float lacunarity);
    bool                                            set_octave_count(unsigned int octave_count);
    void                                            set_seed(int seed);
    void                                            set_quality(noise_quality quality);
private:
    void                                            calculate_weights();
protected:
    virtual void                                    on_configuration_changed() override;
private:
    float                                           _frequency = default_ridged_multifractal_frequency;
    float                                           _lacunarity = default_ridged_multifractal_lacunarity;
    unsigned int                                    _octave_count = default_ridged_multifractal_octave_count;
    int                                             _seed = default_ridged_multifractal_seed;
    noise_quality                                   _quality = default_ridged_multifractal_quality;
    vector<float>                                   _weights = vector<float>(maximum_octave_count);
};

GNOISE_NAMESPACE_END