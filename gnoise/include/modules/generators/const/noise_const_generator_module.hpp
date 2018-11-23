#pragma once

#include "../noise_generator_module.hpp"

GNOISE_NAMESPACE_BEGIN

class noise_const_generator_module : public noise_generator_module
{
public:
    noise_const_generator_module() noexcept = default;
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

    float                                           const_value() const;
    void                                            set_const_value(float value);
protected:
    virtual void                                    on_configuration_changed() override;
private:
    float                                           _const_value = 0.0f;
};

GNOISE_NAMESPACE_END