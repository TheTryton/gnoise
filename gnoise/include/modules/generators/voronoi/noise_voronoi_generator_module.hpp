#pragma once

#include "../noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

inline constexpr float default_voronoi_frequency = 1.0f;
inline constexpr float default_voronoi_displacement = 2.0f;
inline constexpr int default_voronoi_seed = 0;
inline constexpr bool default_voronoi_use_distance = 0;

class noise_voronoi_generator_module : public noise_generator_module
{
public:
    noise_voronoi_generator_module() noexcept = default;
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
    inline float                                    displacement() const;
    inline int                                      seed() const;
    inline bool                                     uses_distance() const;

    void                                            set_frequency(float frequency);
    void                                            set_displacement(float displacement);
    void                                            set_seed(int seed);
    void                                            set_use_distance(bool use_distance);
protected:
    virtual void                                    on_configuration_changed() override;
private:
    float                                           _frequency = default_voronoi_frequency;
    float                                           _displacement = default_voronoi_displacement;
    int                                             _seed = default_voronoi_seed;
    bool                                            _use_distance = default_voronoi_use_distance;
};

GNOISE_NAMESPACE_END